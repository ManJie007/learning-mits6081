Xv6 kernel source files.
File            | Description
bio.c           | Disk block cache for the file system.
console.c       | Connect to the user keyboard and screen.
entry.S         | Very first boot instructions.
exec.c          | exec() system call.
file.c          | File descriptor support.
fs.c            | File system.
kalloc.c        | Physical page allocator.
kernelvec.S     |  Handle traps from kernel, and timer interrupts.
log.c           | File system logging and crash recovery.
main.c          | Control initialization of other modules during boot.
pipe.c          | Pipes.
plic.c          | RISC-V interrupt controller.
printf.c        | Formatted output to the console.
proc.c          | Processes and scheduling.
sleeplock.c     | Locks that yield the CPU.
spinlock.c      | Locks that don’t yield the CPU.
start.c         | Early machine-mode boot code.
string.c        | C string and byte-array library.
swtch.S         | Thread switching.
syscall.c       | Dispatch system calls to handling function.
sysfile.c       | File-related system calls.
sysproc.c       | Process-related system calls.
trampoline.S    | Assembly code to switch between user and kernel.
trap.c          | C code to handle and return from traps and interrupts.
uart.c          | Serial-port console device driver.
virtio\_disk.c   | Disk device driver.
vm.c            | Manage page tables and address spaces.

The xv6 kernel source is in the kernel/ sub-directory.
The inter-module interfaces are defined in defs.h (kernel/defs.h).

Layout of a process's virtual address spaces

|     trampoline     |  <-  MAXVA 
|     trapframe      |
|       heap         |
|     user stack     |
| user test and data |  <-  0

Xv6 uses page tables (which are implemented by hardware) to give each process its own address space.

Xv6 maintains a separate page table for each process that defines that process’s address space

 There are a number of factors that limit the maximum size of a process’s address space: pointers on the RISC-V are 64 bits wide; the hardware only uses the low 39 bits when looking up virtual addresses in page tables; and xv6 only uses 38 of those 39 bits. Thus, the maximum address is 2 ^ 38 − 1 = 0x3fffffffff, which is MAXVA (kernel/riscv.h:363).

!!!!!!
At the top of the address space xv6 reserves a page for a trampoline and a page mapping the process’s trapframe. Xv6 uses these two pages to transition into the kernel and back; the trampoline page contains the code to transition in and out of the kernel and mapping the trapframe is necessary to save/restore the state of the user process, as we will explain in Chapter 4.
!!!!!!

The xv6 kernel maintains many pieces of state for each process, which it gathers into a struct proc (kernel/proc.h:86).

Each process has a thread of execution (or thread for short) that executes the process’s instructions. A thread can be suspended and later resumed. To switch transparently between processes, the kernel suspends the currently running thread and resumes another process’s thread. 

!!!!!!
Much of the state of a thread (local variables, function call return addresses) is stored on the thread’s stacks.
!!!!!!

!!!!!!
Each process has two stacks: a user stack and a kernel stack (p-\>kstack). 
!!!!!!

When the process is executing user instructions, only its user stack is in use, and its kernel stack is empty. When the process enters the kernel (for a system call or interrupt), the kernel code executes on the process’s kernel stack; while a process is in the kernel, its user stack still contains saved data, but isn’t actively used. A process’s thread alternates between actively using its user stack and its kernel stack.The kernel stack is separate (and protected from user code) so that the kernel can execute even if a process has wrecked its user stack.

!!!!!!
A process can make a system call by executing the RISC-V ecall instruction. This instruction raises the hardware privilege level and changes the program counter to a kernel-defined entry point. The code at the entry point switches to a kernel stack and executes the kernel instructions that implement the system call. 
!!!!!!

!!!!!!
When the system call completes, the kernel switches back to the user stack and returns to user space by calling the sret instruction, which lowers the hardware privilege level and resumes executing user instructions just after the system call instruction. 
!!!!!!

A process’s thread can “block” in the kernel to wait for I/O, and resume where it left off when the I/O has finished.

!!!!!!
p-\>pagetable holds the process’s page table, in the format that the RISC-V hardware expects. Xv6 causes the paging hardware to use a process’s p-\>pagetable when executing that process in user space. A process’s page table also serves as the record of the addresses of the physical pages allocated to store the process’s memory.
!!!!!!

In xv6, a process consists of one address space and one thread. In real operating systems a process may have more than one thread to take advantage of multiple CPUs.

!!!!!!
Code: starting xv6, the first process and system call

1.When the RISC-V computer powers on, it initializes itself and runs a boot loader which is stored in read-only memory. 
    The boot loader loads the xv6 kernel into memory. Then, in machine mode, the CPU executes xv6 starting at \_entry (kernel/entry.S:7). 
    The RISC-V starts with paging hardware disabled: virtual addresses map directly to physical addresses.
    The loader loads the xv6 kernel into memory at physical address 0x80000000. The reason it places the kernel at 0x80000000 rather than 0x0 is because the address range 0x0:0x80000000 contains I/O devices.

2.The instructions at \_entry set up a stack so that xv6 can run C code. Xv6 declares space for an initial stack, stack0, in the file start.c (kernel/start.c:11). 
    The code at \_entry loads the stack pointer register sp with the address stack0+4096, the top of the stack, because the stack on RISC-V grows down. Now that the kernel has a stack, \_entry calls into C code at start (kernel/start.c:21).

3.The function start performs some configuration that is only allowed in machine mode, and then switches to supervisor mode. 
    To enter supervisor mode, RISC-V provides the instruction mret. 
        This instruction is most often used to return from a previous call from supervisor mode to machine mode. 
3.1 start isn’t returning from such a call, and instead sets things up as if there had been one: it sets the previous privilege mode to supervisor in the register mstatus, it sets the return address to main by writing main’s address into the register mepc, disables virtual address translation in supervisor mode by writing 0 into the page-table register satp, and delegates all interrupts and exceptions to supervisor mode.

3.2 Before jumping into supervisor mode, start performs one more task: it programs the clock chip to generate timer interrupts. 

3.3 With this housekeeping out of the way, start “returns” to supervisor mode by calling mret. This causes the program counter to change to main (kernel/main.c:11).

4.After main (kernel/main.c:11) initializes several devices and subsystems, it creates the first process by calling userinit (kernel/proc.c:226). 
    The first process executes a small program written in RISC-V assembly, make makes the first system call in xv6. initcode.S (user/initcode.S:3) loads the number for the exec system call, SYS\_EXEC (kernel/syscall.h:8), into register a7, and then calls ecall to re-enter the kernel.
    The kernel uses the number in register a7 in syscall (kernel/syscall.c:133) to call the desired system call. The system call table (kernel/syscall.c:108) maps SYS\_EXEC to sys\_exec, which the kernel invokes. As we saw in Chapter 1, exec replaces the memory and registers of the current process with a new program (in this case, /init).

5.Once the kernel has completed exec, it returns to user space in the /init process. Init (user/init.c:15) creates a new console device file if needed and then opens it as file descriptors 0, 1, and 2. Then it starts a shell on the console. The system is up.
!!!!!!
