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

 There are a number of factors that limit the maximum size of a process’s address space: pointers on the RISC-V are 64 bits wide; the hardware only uses the low 39 bits when looking up virtual addresses in page tables; and xv6 only uses 38 of those 39 bits. Thus, the maximum address is 2 ^ 38 − 1 = 0x3fffffffff, which is #MAXVA (kernel/riscv.h:363).

**
At the top of the address space xv6 reserves a page for a #trampoline and a page mapping the process’s #trapframe. Xv6 uses these two pages to transition into the kernel and back; the trampoline page contains the code to transition in and out of the kernel and mapping the trapframe is necessary to save/restore the state of the user process, as we will explain in Chapter 4.
**

The xv6 kernel maintains many pieces of state for each process, which it gathers into a struct #proc (kernel/proc.h:86).

Each process has a thread of execution (or thread for short) that executes the process’s instructions. A thread can be suspended and later resumed. To switch transparently between processes, the kernel suspends the currently running thread and resumes another process’s thread. 

**
Much of the state of a thread (local variables, function call return addresses) is stored on the thread’s stacks.
**

**
Each process has two stacks: a user stack and a kernel stack (p-\>kstack). 
**

When the process is executing user instructions, only its user stack is in use, and its kernel stack is empty. When the process enters the kernel (for a system call or interrupt), the kernel code executes on the process’s kernel stack; while a process is in the kernel, its user stack still contains saved data, but isn’t actively used. A process’s thread alternates between actively using its user stack and its kernel stack.The kernel stack is separate (and protected from user code) so that the kernel can execute even if a process has wrecked its user stack.

**
A process can make a system call by executing the RISC-V ecall instruction. This instruction raises the hardware privilege level and changes the program counter to a kernel-defined entry point. The code at the entry point switches to a kernel stack and executes the kernel instructions that implement the system call. 
**

**
When the system call completes, the kernel switches back to the user stack and returns to user space by calling the #sret instruction, which lowers the hardware privilege level and resumes executing user instructions just after the system call instruction. 
**

A process’s thread can “block” in the kernel to wait for I/O, and resume where it left off when the I/O has finished.

**
p-\>pagetable holds the process’s page table, in the format that the RISC-V hardware expects. Xv6 causes the paging hardware to use a process’s p-\>pagetable when executing that process in user space. A process’s page table also serves as the record of the addresses of the physical pages allocated to store the process’s memory.
**

In xv6, a process consists of one address space and one thread. In real operating systems a process may have more than one thread to take advantage of multiple CPUs.

**
Code: starting xv6, the first process and system call

1.When the RISC-V computer powers on, it initializes itself and runs a boot loader which is stored in read-only memory. 
    The boot loader loads the xv6 kernel into memory. Then, in machine mode, the CPU executes xv6 starting at #\_entry (kernel/entry.S:7). 
    The RISC-V starts with paging hardware disabled: virtual addresses map directly to physical addresses.
    The loader loads the xv6 kernel into memory at physical address 0x80000000. The reason it places the kernel at 0x80000000 rather than 0x0 is because the address range 0x0:0x80000000 contains I/O devices.

2.The instructions at \_entry set up a stack so that xv6 can run C code. Xv6 declares space for an initial stack, #stack0, in the file #start.c (kernel/start.c:11). 
    The code at \_entry loads the stack pointer register sp with the address stack0+4096, the top of the stack, because the stack on RISC-V grows down. Now that the kernel has a stack, \_entry calls into C code at #start (kernel/start.c:21).

3.The function start performs some configuration that is only allowed in machine mode, and then switches to supervisor mode. 
    To enter supervisor mode, RISC-V provides the instruction #mret. 
        This instruction is most often used to return from a previous call from supervisor mode to machine mode. 
3.1 start isn’t returning from such a call, and instead sets things up as if there had been one: it sets the previous privilege mode to supervisor in the register #mstatus, it sets the return address to main by writing main’s address into the register #mepc, disables virtual address translation in supervisor mode by writing 0 into the page-table register #satp, and delegates all interrupts and exceptions to supervisor mode.

3.2 Before jumping into supervisor mode, start performs one more task: it programs the #clock chip to generate timer interrupts. 

3.3 With this housekeeping out of the way, start “returns” to supervisor mode by calling #mret. This causes the program counter to change to #main (kernel/main.c:11).

4.After main (kernel/main.c:11) initializes several devices and subsystems, it creates the first process by calling #userinit (kernel/proc.c:226). 
    The first process executes a small program written in RISC-V assembly, make makes the first system call in xv6. #initcode.S (user/initcode.S:3) loads the number for the exec system call, #SYS\_EXEC (kernel/syscall.h:8), into register a7, and then calls #ecall to re-enter the kernel.
    The kernel uses the number in register a7 in #syscall (kernel/syscall.c:133) to call the desired system call. The system call #table (kernel/syscall.c:108) maps SYS\_EXEC to sys\_exec, which the kernel invokes. As we saw in Chapter 1, exec replaces the memory and registers of the current process with a new program (in this case, #/init).

5.Once the kernel has completed exec, it returns to user space in the /init process. Init (user/init.c:15) creates a new #console device file if needed and then opens it as file descriptors 0, 1, and 2. Then it starts a shell on the console. The system is up.
**

Code: Calling system calls

Chapter 2 ended with #initcode.S invoking the #exec system call (user/initcode.S:11). Let’s look at how the user call makes its way to the exec system call’s implementation in the kernel.

**
initcode.S places the arguments for exec in registers a0 and a1, and puts the system call number in a7. System call numbers match the entries in the #syscalls array, a table of function pointers (kernel/syscall.c:108). The #ecall instruction traps into the kernel and causes #uservec, #usertrap, and then syscall to execute, as we saw above.
**

**
syscall (kernel/syscall.c:133) retrieves the system call number from the saved a7 in the #trapframe and uses it to index into syscalls. For the first system call, a7 contains #SYS\_exec (kernel/syscall.h:8), resulting in a call to the system call implementation function #sys\_exec.
**

**
When sys\_exec returns, syscall records its return value in p-\>trapframe-\>a0. 
**

This will cause the original user-space call to exec() to return that value, since the C calling convention on RISC-V places return values in a0. System calls conventionally return negative numbers to indicate errors, and zero or positive numbers for success. If the system call number is invalid, syscall prints an error and returns −1.

Code: System call arguments

System call implementations in the kernel need to find the arguments passed by user code. Because user code calls system call wrapper functions, the arguments are initially where the RISC-V C calling convention places them: !!!in registers.!!!

**
The kernel trap code saves user registers to the current process’s trap frame, where kernel code can find them. 
**

The kernel functions #argint, #argaddr, and #argfd retrieve the n ’th system call argument from the trap frame as an integer, pointer, or a file descriptor. They all call #argraw to retrieve the appropriate saved user register (kernel/syscall.c:35).

Some system calls pass pointers as arguments, and the kernel must use those pointers to read or write user memory.
These pointers pose two challenges. 
    First, the user program may be buggy or malicious, and may pass the kernel an invalid pointer or a pointer intended to trick the kernel into accessing kernel memory instead of user memory. 
    **
    Second, the xv6 kernel page table mappings are not the same as the user page table mappings, so the kernel cannot use ordinary instructions to load or store from user-supplied addresses.
    **
The kernel implements functions that safely transfer data to and from user-supplied addresses.
    #fetchstr is an example (kernel/syscall.c:25). File system calls such as exec use #fetchstr to retrieve string file-name arguments from user space. 
    #fetchstr calls #copyinstr to do the hard work.
    #copyinstr (kernel/vm.c:398) copies up to max bytes to dst from virtual address srcva in the user page table pagetable.
        Since pagetable is not the current page table, #copyinstr uses #walkaddr (which calls #walk) to look up srcva in pagetable, yielding physical address pa0. The kernel maps each physical RAM address to the corresponding kernel virtual address, so copyinstr can directly copy string bytes from pa0 to dst. 
    #walkaddr (kernel/vm.c:104) checks that the user-supplied virtual address is part of the process’s user address space, so programs cannot trick the kernel into reading other memory. A similar function, #copyout, copies data from the kernel to a user-supplied address.

registers:
读寄存器
  uint64 x;
  asm volatile("csrr %0, 寄存器" : "=r" (x) );
写寄存器
  uint64 x;
  asm volatile("csrw 寄存器, %0" : : "r" (x));


mhartid 用于获取当前 CPU 的硬件线程 ID（Hardware Thread ID）。
mstatus 用于存储机器模式（Machine Mode）下的状态信息。这个寄存器包含了一系列的位域，每个位域表示了不同的状态信息或控制位。一些常见的位域包括：
        MPP (Machine Previous Privilege): 用于保存上一个特权级别的信息。
        MPIE (Machine Previous Interrupt Enable): 保存上一个特权级别中断使能位的信息。
        MIE (Machine Interrupt Enable): 机器模式中断使能位，用于控制中断是否被允许触发。
        MPRV (Machine Previous Privilege): 保存上一个特权级别的访存控制信息。
        MXR (Make eXecutable Readable): 控制是否允许执行从只读页面读取指令。
mepc    // machine exception program counter, holds the instruction address to which a return from exception will go.
satp    // supervisor address translation and protection;holds the address of the page table.
medeleg 用于配置机器模式下的异常委托（Exception Delegation）。异常委托允许将特定的异常类型委托给更低特权级别的处理器状态处理，从而允许更高特权级别的代码捕获和处理这些异常。
            具体来说，medeleg 中的每个位代表一种异常类型，如果相应的位被设置为 1，则表示将该异常委托给更低特权级别的处理器状态处理。常见的异常类型包括：
                指令访存错误（Instruction Access Fault）
                加载错误（Load Fault）
                存储错误（Store Fault）
                指令不合法（Illegal Instruction）
                断点（Breakpoint）
                系统调用（System Call）
            通过配置 medeleg，可以灵活地控制哪些异常会传递给更低特权级别的处理器状态处理。这对于操作系统和异常处理机制非常重要，因为它们需要能够适当地处理和恢复从更低特权级别传递上来的异常。
mideleg 用于配置机器模式下的中断委托（Interrupt Delegation）。与异常委托类似，中断委托允许将特定的中断类型委托给更低特权级别的处理器状态处理。
            具体来说，mideleg 中的每个位代表一种中断类型，如果相应的位被设置为 1，则表示将该中断委托给更低特权级别的处理器状态处理。常见的中断类型包括：
                用户软件中断（User Software Interrupt）
                监管模式软件中断（Supervisor Software Interrupt）
                用户定时器中断（User Timer Interrupt）
                监管模式定时器中断（Supervisor Timer Interrupt）
                用户外部中断（User External Interrupt）
                监管模式外部中断（Supervisor External Interrupt）
            通过配置 mideleg，可以灵活地控制哪些中断会传递给更低特权级别的处理器状态处理。这对于操作系统和中断处理机制非常重要，因为它们需要能够适当地处理和响应来自更低特权级别的中断。
sie     "SIE" 表示 "Supervisor Interrupt Enable"，即监管者模式中断使能。这个术语通常用来描述监管者模式（Supervisor Mode）下的中断使能状态。监管者模式是 RISC-V 中的一种特权级别，比用户模式更高，但比机器模式更低。
        SIE 控制是否允许在监管者模式下触发中断。如果 SIE 被置位（设置为 1），则允许中断触发，如果被清零（设置为 0），则禁止中断触发。当 SIE 被清零时，即使有中断请求，处理器也不会响应中断。
        通过操纵 SIE 寄存器，操作系统可以在需要时启用或禁用中断响应，从而实现对中断的灵活控制。这对于操作系统的正确功能和性能至关重要。
pmpaddr0 用于配置物理内存保护（Physical Memory Protection，PMP）。PMP 允许对物理内存的访问进行细粒度的控制，以实现安全和隔离。
            在 PMP 中，pmpaddr0 寄存器用于指定第一个 PMP 区域（Region）的起始地址。PMP 区域是一段连续的物理内存，可以通过配置 PMP 寄存器来定义其访问权限。pmpaddr0 寄存器通常是一个 64 位的寄存器，因为 RISC-V 架构中的物理地址是 64 位的。 通过配置 pmpaddr0 寄存器，可以定义第一个 PMP 区域的起始地址，从而限制对该区域的访问。其他的 PMP 寄存器则用于指定更多的 PMP 区域，以实现更复杂的内存访问控制策略。 
            需要注意的是，PMP 寄存器只在特权级别（例如，监管者模式）下才能访问和配置，通常由操作系统或安全监控程序使用来确保系统的安全性和隔离性。
pmpcfg0 用于配置物理内存保护（Physical Memory Protection，PMP）的区域属性。PMP 允许对物理内存的访问进行细粒度的控制，以实现安全和隔离。
            在 PMP 中，pmpcfg0 寄存器用于指定第一个 PMP 区域（Region）的配置信息。这个寄存器通常是一个 8 位的寄存器，每个位对应一个 PMP 区域的配置。每个 PMP 区域可以配置为以下之一：
                不可访问（No Access）
                只读（Read-Only）
                读写（Read-Write）
                执行禁止（Execute Disable）
            通过配置 pmpcfg0 寄存器，可以指定第一个 PMP 区域的访问属性，从而限制对该区域的读、写和执行权限。其他的 PMP 寄存器用于指定更多的 PMP 区域和它们的属性，以实现更复杂的内存访问控制策略。
            需要注意的是，PMP 寄存器只在特权级别（例如，监管者模式）下才能访问和配置，通常由操作系统或安全监控程序使用来确保系统的安全性和隔离性。
mscratch 通常用于存储机器模式下的软件上下文信息，比如异常处理时保存现场。
mtvec    Machine-mode interrupt vector 用于设置机器模式（Machine Mode）中断处理的向量基地址的特权寄存器。这个寄存器存储了一个指针，指向用于处理异常和中断的中断处理程序（interrupt handler）的入口点。当发生中断或异常时，处理器会跳转到mtvec 寄存器指定的地址处执行相应的处理程序。
mie      MIE 寄存器是 Machine Interrupt Enable 寄存器，用于控制机器级中断的使能状态。该寄存器的位布局如下：
                Bit 0: 软件中断使能（MSIE）
                Bit 1: 时钟中断使能（MTIE）
                Bit 3: 外部中断使能（MEIE）
            这些位控制着不同类型的中断是否被启用。如果某一位被设置为 1，表示对应类型的中断被启用；如果被设置为 0，则表示禁用。
            通常，操作系统或者应用程序会使用 CSR（Control and Status Register，控制和状态寄存器）指令来读取或者写入 MIE 寄存器，以控制和管理中断的行为。
tp          tp 寄存器是线程指针寄存器，用于存储当前线程的指针。这个寄存器通常被用于线程的上下文切换和处理，以及访问线程局部存储（TLS，Thread-Local Storage）。

kernel.ld   定义了内核是如何被加载的
entry.s XV6从entry.s开始启动，这个时候没有内存分页，没有隔离性，并且运行在M-mode（machine mode）。
main函数:
    consoleinit的函数，它的工作与你想象的完全一样，也就是设置好console。
    kinit：设置好页表分配器（page allocator）
    kvminit：设置好虚拟内存，这是下节课的内容
    kvminithart：打开页表，也是下节课的内容
    processinit：设置好初始进程或者说设置好进程表单
    trapinit/trapinithart：设置好user/kernel mode转换代码
    plicinit/plicinithart：设置好中断控制器PLIC（Platform Level Interrupt Controller），我们后面在介绍中断的时候会详细的介绍这部分，这是我们用来与磁盘和console交互方式
    binit：分配buffer cache
    iinit：初始化inode缓存
    fileinit：初始化文件系统
    virtio\_disk\_init：初始化磁盘
    userinit：最后当所有的设置都完成了，操作系统也运行起来了，会通过userinit运行第一个进程，这里有点意思，接下来我们看一下userinit
    我们总是需要有一个用户进程在运行，这样才能实现与操作系统的交互，所以这里需要一个小程序来初始化第一个用户进程。这个小程序定义在initcode中。这里直接是程序的二进制形式，它会链接或者在内核中直接静态定义。实际上，这段代码对应了下面的汇编程序。/user/initcode.S
    userinit会创建初始进程，返回到用户空间，执行刚刚介绍的3条指令，再回到内核空间。initcode完成了通过exec调用init程序。
