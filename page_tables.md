Page tables are a popular design because they provide a level of indirection that allow operating systems to perform many tricks. 
**
    xv6 performs a few tricks: mapping the same memory (a trampoline page) in several address spaces, and guarding kernel and user stacks with an unmapped page.
**

xv6 runs on Sv39 RISC-V, which means that only the bottom 39 bits of a 64-bit virtual address are used; the top 25 bits are not used.
In Sv39 RISC-V, the top 25 bits of a virtual address are not used for translation.

In this Sv39 configuration, a RISC-V page table is logically an array of 2 ^ 27 (134,217,728) page table entries (#PTEs). 
Each #PTE contains a 44-bit physical page number (PPN) and some flags. 
The paging hardware translates a virtual address by using the top 27 bits of the 39 bits to index into the page table to find a PTE, and making a 56-bit physical address whose top 44 bits come from the PPN in the PTE and whose bottom 12 bits are copied from the original virtual address.

        Virtual address
    25       27       12
[  EXT  |  Index  |  Offset]-----------------------------------
            |                                                 |
            |        44      10                               |
            |     ---------------                             |
            |     |       |      | 2 ^ 27                     |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |     |       |      |                            |
            |---> |  PPN  | Flags|                            |
                  |   |---------------------------------      |
                  |       |      | 1                   |      |
                  |       |      | 0                   |      |
                  ---------------                      |      |
                    page tables                        |      |
                                                       |      |
                                                       |      |
                                                       v      v
                                                    [      |    ]
                                                       44     12
                                                   Physical Address

A page table gives the operating system control over virtual-to-physical address translations at the granularity of aligned chunks of 4096 (2 ^ 12) bytes. Such a chunk is called a page.

A RISC-V CPU translates a virtual address into a physical in three steps. A page table is stored in physical memory as a three-level tree. 
The root of the tree is a 4096-byte page-table page that contains 512 PTEs, which contain the physical addresses for page-table pages in the next level of the tree. 
Each of those pages contains 512 PTEs for the final level in the tree. 
The paging hardware uses the top 9 bits of the 27 bits to select a PTE in the root page-table page, the middle 9 bits to select a PTE in a page-table page in the next level of the tree, and the bottom 9 bits to select the final PTE. (In Sv48 RISC-V a page table has four levels, and bits 39 through 47 of a virtual address index into the top-level.

                                                      Virtual address                                                                     Physical Address                                                   
                                                          9     9      9       12                                                           44       12                                                      
                                          --->[  EXT  |  L2  |  L1  |  L0  |  Offset  ]                                                  [  PPN  |  Offset  ]                                              
                                                          |      |      |       |                                                            ^        ^                                                       
          ------------------------------------------------|      |      |       |                                                            |        |                                                    
          |                                                      |      |       |------------------------------------------------------------|--------|                                                      
          |          44      10                                  |      |                                                                    | 
          |        --------------                                |      |---------|                                                          |
          |       |       |      | 511          -----------------|                |           ------------------------------------------------      
          |       |       |      |              |                                 |           |
          |       |       |      |              |        44      10               |           |  
          |--------->PPN  | Flags|              |      --------------             |           |
                  |   |   |      |              |     |       |      | 511        |           |
                  |   |   |      |              |     |       |      |            |           |
                  |   |   |      | 0            |     |       |      |            |           |
                   ---|----------               |------->PPN  | Flags|            |           |                      
                    Page Directory                    |   |   |      |            |           |                                                                 
                      |                               |   |   |      |            |           |                                                     
                      |                               |   |   |      | 0          |           |                                              
                      | -----------------------------> ---|----------             |          4|4     10                                                          
                                                        Page Directory            |        ---|----------     
                                                          |                       |       |   |   |      | 511
                                                          |                       |       |   |   |      |    
                                                          |                       |       |   |   |      |    
                                                          |                       |--------->PPN  | Flags|    
                                                          |                               |       |      |    
                                                          |                               |       |      |    
                                                          |                               |       |      | 0  
                                                          |------------------------------> --------------     
                                                                                            Page Directory    
                                                                                                                                                                                                      
                                                                                                                                                                                                      
                            63            53                    10 9     8   7     6     5     4     3     2     1     0                                                                              
                            [  Reserved  |  Physical Page Number  |  RSW  |  D  |  A  |  G  |  U  |  X  |  W  |  R  |  V  ]                                                                           
                                                                                                                             V - Valid
                                                                                                                             R - Readable
                                                                                                                             W - Writeable
                                                                                                                             X - Executable
                                                                                                                             U - User
                                                                                                                             G - Global
                                                                                                                             A - Accessed
                                                                                                                             D - Dirty (0 in page directory)
                                                                                                                           RSW - Reserved for supervisor software
                                                                                                                                                                                                      

If any of the three PTEs required to translate an address is not present, the paging hardware raises a #page-fault exception, leaving it up to the kernel to handle the exception (see Chapter 4).

The three-level structure of Figure 3.2 allows a memory-efficient way of recording PTEs, compared to the single-level design of Figure 3.1. In the common case in which large ranges of virtual addresses have no mappings, the three-level structure can omit entire page directories.

Although a CPU walks the three-level structure in hardware as part of executing a load or store instruction, a potential downside of three levels is that the CPU must load three PTEs from memory to perform the translation of the virtual address in the load/store instruction to a physical address. To avoid the cost of loading PTEs from physical memory, a RISC-V CPU caches page table entries in a Translation Look-aside Buffer (#TLB).

Each PTE contains flag bits that tell the paging hardware how the associated virtual address is allowed to be used. 
        PTE\_V indicates whether the PTE is present: if it is not set, a reference to the page causes an exception (i.e. is not allowed). 
        PTE\_R controls whether instructions are allowed to read to the page. 
        PTE\_W controls whether instructions are allowed to write to the page. 
        PTE\_X controls whether the CPU may interpret the content of the page as instructions and execute them. 
        PTE\_U controls whether instructions in user mode are allowed to access the page; if PTE\_U is not set, the PTE can be used only in supervisor mode. 
        Figure 3.2 shows how it all works. The flags and all other page hardware-related structures are defined in (kernel/riscv.h)


To tell the hardware to use a page table, the kernel must write the physical address of the root page-table page into the #satp register. Each CPU has its own #satp.
Each CPU has its own satp so that different CPUs can run different processes, each with a private address space described by its own page table.

**
Typically a kernel maps all of physical memory into its page table so that it can read and write any location in physical memory using #load/store instructions. 
Since the page directories are in physical memory, the kernel can program the content of a PTE in a page directory by writing to the virtual address of the PTE using a standard store instruction.
**

Physical memory refers to storage cells in DRAM. A byte of physical memory has an address, called a physical address.

Instructions use only virtual addresses, which the paging hardware translates to physical addresses, and then sends to the DRAM hardware to read or write storage. 

                                                                                                                                                                                                           
                                                                                                                                                                                                    
                                                                                                         Physical Addresses                                                                            
                                Virtual Addresses                                              2^56 - 1 --------------------                                                                          
                         MAXVA -------------------                                                      |                  |                                                                             
                               |   Trampoline   | R-X \                                                 |                  |                                                                              
                               |   Guard page   | ---                                                   |                  |                                                                              
                               |   kstack 0     | RW-                                                   |     Unused       |                                                                             
                               |   Guard page   | ---                                                   |                  |                                                                             
                               |   kstack 1     | RW-                                                   |                  |                                                                               
              PHYSTOP  _______ |     ...        |      _______________________________________________  |__________________|                                                                             
          (0x86400000)         |                |                                                       |                  |                                                                                
                               |   Free memory  | RW-                                                   |                  |                                                                            
                               |                |      _______________________________________________  |Physical memory(RA|M)                                                                          
                               |   Kernel data  | RW-  _______________________________________________  |                  |                                                                            
              KERNBASE  ______ |   Kernel text  | R-X  _______________________________________________  |__________________|                                                                            
          (0x80000000)         |                |                                                       |Unused            |                                                                            
                               |                |                                                       |and other I/O devi|ces                                                                         
                               |                |                                                       |                  |                                                                            
           0x10001000   ______ |  VIRTIO disk   | RW-  _______________________________________________  | VIRTIO disk      |                                                                            
           0x10000000   ______ |    UARTO       | RW-  _______________________________________________  |    UARTO         |                                                                            
                               |                |                                                       |                  |                                                                            
           0x0c000000   ______ |    PLIC        | RW-  _______________________________________________  |     PLIC         |                                                                            
                               |                |                                                       |                  |                                                                            
                               |                |                                  0x02000000   ______  |     CLINT        |                                                                            
                               |                |                                                       |                  |                                                                            
                               |                |                                                       |     Unused       |                                                                            
                               |                |                                                       |                  |                                                                            
                               |                |                                      0x1000   ______  |     boot ROM     |                                                                            
                               |                |                                                       |     Unused       |                                                                            
                     0  ------ ------------------                                           0   ------  --------------------

Kernel address space
Xv6 maintains one page table per process, describing each process’s user address space, plus a single page table that describes the kernel’s address space.
The file (kernel/#memlayout.h) declares the constants for xv6’s kernel memory layout.

QEMU simulates a computer that includes #RAM (physical memory) starting at physical address #0x80000000 and continuing through at least #0x86400000, which xv6 calls #PHYSTOP.

The QEMU simulation also includes I/O devices such as a disk interface. QEMU exposes the device interfaces to software as #memory-mapped #control #registers that sit below #0x80000000 in the physical address space. The kernel can interact with the devices by reading/writing these special physical addresses; such reads and writes communicate with the device hardware rather than with RAM.

**
The kernel gets at RAM and memory-mapped device registers using “direct mapping;” 
**
that is, mapping the resources at virtual addresses that are #equal to the physical address. For example, the kernel itself is located at #KERNBASE=0x80000000 in both the virtual address space and in physical memory. Direct mapping simplifies kernel code that reads or writes physical memory.

There are a couple of kernel virtual addresses that aren’t direct-mapped:
    The trampoline page. It is mapped at the top of the virtual address space; user page tables have this same mapping. Chapter 4 discusses the role of the trampoline page, but we see here an interesting use case of page tables; **a physical page (holding the trampoline code) is mapped twice in the virtual address space of the kernel: once at top of the virtual address space and once with a direct mapping.**
    The kernel stack pages. Each process has its own kernel stack, which is mapped high so that below it xv6 can leave an unmapped guard page. The guard page’s PTE is invalid (i.e., PTE\_V is not set), so that if the kernel overflows a kernel stack, it will likely cause an exception and the kernel will panic. Without a guard page an overflowing stack would overwrite other kernel memory, resulting in incorrect operation. A panic crash is preferable.
    While the kernel uses its stacks via the high-memory mappings, they are also accessible to the kernel through a direct-mapped address. An alternate design might have just the direct mapping, and use the stacks at the direct-mapped address. In that arrangement, however, providing guard pages would involve unmapping virtual addresses that would otherwise refer to physical memory, which would then be hard to use.

Code: creating an address space

Most of the xv6 code for manipulating address spaces and page tables resides in vm.c (kernel/vm.c:1).

The central data structure is #pagetable\_t, which is really a pointer to a RISC-V root page-table page; a pagetable\_t may be either the kernel page table, or one of the perprocess page tables.

The central functions are #walk, which finds the PTE for a virtual address, and mappages, which installs PTEs for new mappings.
    #walk (kernel/vm.c:81) mimics the RISC-V paging hardware as it looks up the PTE for a virtual address (see Figure 3.2). walk descends the 3-level page table 9 bits at the time. It uses each level’s 9 bits of virtual address to find the PTE of either the next-level page table or the final page (kernel/vm.c:87). If the PTE isn’t valid, then the required page hasn’t yet been allocated; if the alloc argument is set, walk allocates a new page-table page and puts its physical address in the PTE. It returns the address of the PTE in the lowest layer in the tree (kernel/vm.c:97).
**
The above code depends on physical memory being direct-mapped into the kernel virtual address space.
For example, as walk descends levels of the page table, it pulls the (physical) address of the next-level-down page table from a PTE (kernel/vm.c:89), and then uses that address as a virtual address to fetch the PTE at the next level down (kernel/vm.c:87).
**

Functions starting with #kvm manipulate the kernel page table; 

Functions starting with #uvm manipulate a user page table; 

other functions are used for both.

#copyout and #copyin copy data to and from user virtual addresses provided as system call arguments;

Early in the boot sequence, #main calls #kvminit (kernel/vm.c:54) to create the kernel’s page table using #kvmmake (kernel/vm.c:20). This call occurs before xv6 has enabled paging on the RISC-V, so addresses refer directly to physical memory. 

#Kvmmake first allocates a page of physical memory to hold the root page-table page. Then it calls #kvmmap to install the translations that the kernel needs. The translations include the kernel’s instructions and data, physical memory up to #PHYSTOP, and memory ranges which are actually devices. 
    #kvmmap (kernel/vm.c:127) calls #mappages (kernel/vm.c:138), which installs mappings into a page table for a range of virtual addresses to a corresponding range of physical addresses. It does this separately for each virtual address in the range, at page intervals. For each virtual address to be mapped, #mappages calls #walk to find the address of the PTE for that address. It then initializes the PTE to hold the relevant physical page number, the desired permissions (PTE\_W, PTE\_X, and/or PTE\_R), and PTE\_V to mark the PTE as valid (kernel/vm.c:153).

#Proc\_mapstacks (kernel/proc.c:33) allocates a kernel stack for each process. It calls #kvmmap to map each stack at the virtual address generated by #KSTACK, which leaves room for the invalid #stack-guard pages.

#main calls #kvminithart (kernel/vm.c:62) to install the kernel page table. It writes the physical address of the root page-table page into the register #satp. After this the CPU will translate addresses using the kernel page table. Since the kernel uses an identity mapping, the now virtual address of the next instruction will map to the right physical memory address.

Each RISC-V CPU caches page table entries in a Translation Look-aside Buffer (#TLB), and when xv6 changes a page table, it must tell the CPU to invalidate corresponding cached TLB entries.

The RISC-V has an instruction #sfence.vma that flushes the current CPU’s TLB. Xv6 executes #sfence.vma in #kvminithart after reloading the #satp register, and in the trampoline code that switches to a user page table before returning to user space (#kernel/trampoline.S:79).

Physical memory allocation
The kernel must allocate and free physical memory at run-time for page tables, user memory, kernel stacks, and pipe buffers.

xv6 uses the physical memory between #the end of the kernel and #PHYSTOP for run-time allocation. It allocates and frees whole #4096-byte pages at a time. It keeps track of which pages are free by threading a #linked list through the pages themselves. Allocation consists of removing a page from the linked list; freeing consists of adding the freed page to the list.

Code: Physical memory allocator

The allocator resides in #kalloc.c (kernel/kalloc.c:1). The allocator’s data structure is a free #list of physical memory pages that are available for allocation. 

Each free page’s list element is a struct #run (kernel/kalloc.c:17). 

The free list is protected by a #spin lock (kernel/kalloc.c:21-24). The list and the lock are wrapped in a struct to make clear that the lock protects the fields in the struct.

The function #main calls #kinit to initialize the allocator (kernel/kalloc.c:27). #kinit initializes the free list to hold every page between #the end of the kernel and #PHYSTOP. 

xv6 ought to determine how much physical memory is available by parsing configuration information provided by the hardware. Instead xv6 assumes that the machine has 128 megabytes of RAM. 

#kinit calls #freerange to add memory to the free list via per-page calls to #kfree. A PTE can only refer to a physical address that is aligned on a 4096-byte boundary (is a multiple of 4096), so freerange uses #PGROUNDUP to ensure that it frees only aligned physical addresses. The allocator starts with no memory; these calls to #kfree give it some to manage.

The function #kfree (kernel/kalloc.c:47) begins by setting every byte in the memory being freed to the value 1. This will cause code that uses memory after freeing it (uses “dangling references”) to read garbage instead of the old valid contents; hopefully that will cause such code to break faster. 
Then #kfree prepends the page to the free list: it casts pa to a pointer to struct run, records the old start of the free list in r-\>next, and sets the free list equal to r. 

#kalloc removes and returns the first element in the free list.

The allocator sometimes treats addresses as #integers in order to perform arithmetic on them (e.g., traversing all pages in freerange), and sometimes uses addresses as #pointers to read and write memory (e.g., manipulating the run structure stored in each page);





                                MAXVA --> --------------
                                          | trampoline |
                                          | trapframe  |          -----   --------------                                                   
                                          |            |            ^     | argument 0 |
                                          |            |            |     |   ...      |
                                          | heap       |            |     | argument N |
                                          |            |            |     |    0       | nul-terminated string
                                          |            |                  | address of | argument N argv[argc]
                                          |            |          stack   |   ...      |                      
                                          |            |                  | address of | argument 0 argv[0]   
                                PAGESIZE  | stack      |            |     | address of | address of argv[0]  argv argument of main
                                          | guard page |            |     | argc       | address argument of main      
                                          | data       |            |     | 0xFFFFFFF  | return PC of main             
                                          | text       |            v     | (empty)    |                               
                                       0  --------------          -----   --------------

Process address space
Each process has a separate page table, and when xv6 switches between processes, it also changes page tables.

A process’s user memory starts at virtual address #zero and can grow up to #MAXVA (kernel/riscv.h:360), allowing a process to address in principle 256 Gigabytes of memory.

When a process asks xv6 for more user memory, xv6 first uses #kalloc to allocate physical pages. It then adds PTEs to the process’s page table that point to the new physical pages. Xv6 sets the PTE\_W, PTE\_X, PTE\_R, PTE\_U, and PTE\_V flags in these PTEs. Most processes do not use the entire user address space; xv6 leaves PTE\_V clear in unused PTEs.

The kernel maps a page with #trampoline code at the top of the user address space, thus a single page of physical memory shows up in all address spaces.

The #stack is a single #page, and is shown with the initial contents as created by #exec.
     Strings containing the #command-line arguments, as well as an array of pointers to them, are at the very top of the stack. Just under that are values that allow a program to start at main as if the function #main(argc, argv) had just been called.

To detect a user stack overflowing the allocated stack memory, xv6 places an inaccessible #guard page right below the stack by clearing the PTE\_U flag.
    If the user stack overflows and the process tries to use an address below the stack, the hardware will generate a page-fault exception because the guard page is inaccessible to a program running in user mode.
    A real-world operating system might instead automatically allocate more memory for the user stack when it overflows.

Code: sbrk

#Sbrk is the system call for a process to shrink or grow its memory. The system call is implemented by the function #growproc (kernel/proc.c:253). #growproc calls #uvmalloc or #uvmdealloc, depending on whether n is postive or negative. #uvmalloc (kernel/vm.c:221) allocates physical memory with #kalloc, and adds #PTEs to the user page table with #mappages. #uvmdealloc calls #uvmunmap (kernel/vm.c:166), which uses #walk to find PTEs and #kfree to free the physical memory they refer to.

Code: exec

#Exec is the system call that creates the user part of an address space. It initializes the user part of an address space from a file stored in the file system. 

#Exec (kernel/exec.c:13) opens the named binary path using #namei (kernel/exec.c:26), which is explained in Chapter 8. Then, it reads the #ELF header. Xv6 applications are described in the widely-used ELF format, defined in (kernel/#elf.h). 
    An ELF binary consists of an ELF header, struct #elfhdr (kernel/elf.h:6), followed by a sequence of program section headers, struct #proghdr (kernel/elf.h:25). Each proghdr describes a section of the application that must be loaded into memory; xv6 programs have only one program section header, but other systems might have separate sections for instructions and data.

The first step is a quick check that the file probably contains an ELF binary. An ELF binary starts with the four-byte “#magic #number” 0x7F, ‘E’, ‘L’, ‘F’, or ELF\_MAGIC (kernel/elf.h:3). If
the ELF header has the right magic number, exec assumes that the binary is well-formed.

#Exec allocates a new page table with no user mappings with #proc\_pagetable (kernel/exec.c:38), allocates memory for each ELF segment with #uvmalloc (kernel/exec.c:52), and loads each segment into memory with #loadseg (kernel/exec.c:10). #loadseg uses #walkaddr to find the physical address of the allocated memory at which to write each page of the ELF segment, and #readi to read from the file.

The program section header for #/init, the first user program created w
th exec, looks like this:

$objdump -p _init
_init:     file format elf64-little

Program Header:
0x70000003 off    0x0000000000000aa3 vaddr 0x0000000000000000 paddr 0x0000000000000000 align 2**0
         filesz 0x0000000000000033 memsz 0x0000000000000000 flags r--
    LOAD off    0x00000000000000e8 vaddr 0x0000000000000000 paddr 0x0000000000000000 align 2**3
         filesz 0x0000000000000990 memsz 0x00000000000009a8 flags rwx
   STACK off    0x0000000000000000 vaddr 0x0000000000000000 paddr 0x0000000000000000 align 2**4
         filesz 0x0000000000000000 memsz 0x0000000000000000 flags rw-

The program section header’s #filesz may be less than the #memsz, indicating that the gap between them should be filled with zeroes (for C global variables) rather than read from the file.

For #/init, filesz is 2112 bytes and memsz is 2136 bytes, and thus #uvmalloc allocates enough physical memory to hold 2136 bytes, but reads only 2112 bytes from the file /init.

Now #exec allocates and initializes the #user #stack. It allocates just one stack page. Exec copies the argument strings to the top of the stack one at a time, recording the pointers to them in ustack. It places a null pointer at the end of what will be the argv list passed to main. The first three entries in ustack are the fake return program counter, argc, and argv pointer.

Exec places an #inaccessible #page just below the stack page, so that programs that try to use more than one page will fault. This inaccessible page also allows exec to deal with arguments that are too large; in that situation, the #copyout (kernel/vm.c:347) function that exec uses to copy arguments to the stack will notice that the destination page is not accessible, and will return -1.

During the preparation of the new memory image, if #exec detects an error like an invalid program segment, it jumps to the label #bad, frees the new image, and returns -1. #Exec must wait to free the old image until it is sure that the system call will succeed: if the old image is gone, the system call cannot return -1 to it. The only error cases in #exec happen during the creation of the image. Once the image is complete, exec can commit to the new #page #table (kernel/exec.c:113) and free the old one (kernel/exec.c:117).

#Exec loads bytes from the ELF file into memory at addresses specified by the ELF file. Users or processes can place whatever addresses they want into an ELF file. Thus exec is risky, because the addresses in the ELF file may refer to the kernel, accidentally or on purpose.  Xv6 performs a number of checks to avoid these risks. For example #if(ph.vaddr + ph.memsz < ph.vaddr) checks for whether the sum overflows a 64-bit integer. The danger is that a user could construct an ELF binary with a ph.vaddr that points to a user-chosen address, and ph.memsz large enough that the sum overflows to 0x1000, which will look like a valid value. 

**
In an older version of xv6 in which the user address space also contained the kernel (but not readable/writable in user mode), the user could choose an address that corresponded to kernel memory and would thus copy data from the ELF binary into the kernel. In the RISC-V version of xv6 this cannot happen, because the kernel has its own separate page table; #loadseg loads into the process’s page table, not in the kernel’s page table.
**
