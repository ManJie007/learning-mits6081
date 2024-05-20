diff --color -r ../../xv6-labs-2021/.git/COMMIT_EDITMSG xv6-labs-2021/.git/COMMIT_EDITMSG
1c1
< add lab exercise 1 xargs
---
> Detecting which pages have been accessed
diff --color -r ../../xv6-labs-2021/.git/FETCH_HEAD xv6-labs-2021/.git/FETCH_HEAD
1c1
< f654383cdec479c9d53a02bffa1ab5526f6c3ca4		branch 'util' of git://g.csail.mit.edu/xv6-labs-2021
---
> 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07		branch 'pgtbl' of git://g.csail.mit.edu/xv6-labs-2021
7d6
< 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07	not-for-merge	branch 'pgtbl' of git://g.csail.mit.edu/xv6-labs-2021
11a11
> f654383cdec479c9d53a02bffa1ab5526f6c3ca4	not-for-merge	branch 'util' of git://g.csail.mit.edu/xv6-labs-2021
Binary files ../../xv6-labs-2021/.git/index and xv6-labs-2021/.git/index differ
diff --color -r ../../xv6-labs-2021/.git/logs/HEAD xv6-labs-2021/.git/logs/HEAD
7c7,15
< 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07 MANJIE007 <297867870@qq.com> 1716184392 +0800	checkout: moving from syscall to pgtbl
---
> 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af bae676bbb85aa0f99ad21d59ae2e6bd174ee753e manjie007 <297867870@qq.com> 1715325821 +0000	checkout: moving from syscall to util
> bae676bbb85aa0f99ad21d59ae2e6bd174ee753e 288664627b747fc75e67a053eda795a7b6355800 manjie007 <297867870@qq.com> 1715327851 +0000	commit: add lab exercise fix xargs
> 288664627b747fc75e67a053eda795a7b6355800 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af manjie007 <297867870@qq.com> 1715327856 +0000	checkout: moving from util to syscall
> 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 manjie007 <297867870@qq.com> 1715611873 +0000	commit: system call trace
> 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 fbe7d4e93ef20a566c8cb9db4ae59abeca4e7a0f manjie007 <297867870@qq.com> 1715658098 +0000	commit: system call sysinfo
> fbe7d4e93ef20a566c8cb9db4ae59abeca4e7a0f 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07 manjie007 <297867870@qq.com> 1715777471 +0000	checkout: moving from syscall to pgtbl
> 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07 e922be3a89048dc3b06ae0b1f33a651b37ec5372 manjie007 <297867870@qq.com> 1715930643 +0000	commit: Speed up system calls
> e922be3a89048dc3b06ae0b1f33a651b37ec5372 a2e7e9ac51507c90565458d9a053bb709c7527c1 manjie007 <297867870@qq.com> 1716172150 +0000	commit: Print a page table
> a2e7e9ac51507c90565458d9a053bb709c7527c1 694b5e6c47661fc447ef4a8ac1686c2986d034dc manjie007 <297867870@qq.com> 1716184049 +0000	commit: Detecting which pages have been accessed
diff --color -r ../../xv6-labs-2021/.git/logs/refs/heads/pgtbl xv6-labs-2021/.git/logs/refs/heads/pgtbl
1c1,4
< 0000000000000000000000000000000000000000 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07 MANJIE007 <297867870@qq.com> 1716184392 +0800	branch: Created from refs/remotes/origin/pgtbl
---
> 0000000000000000000000000000000000000000 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07 manjie007 <297867870@qq.com> 1715777471 +0000	branch: Created from refs/remotes/origin/pgtbl
> 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07 e922be3a89048dc3b06ae0b1f33a651b37ec5372 manjie007 <297867870@qq.com> 1715930643 +0000	commit: Speed up system calls
> e922be3a89048dc3b06ae0b1f33a651b37ec5372 a2e7e9ac51507c90565458d9a053bb709c7527c1 manjie007 <297867870@qq.com> 1716172150 +0000	commit: Print a page table
> a2e7e9ac51507c90565458d9a053bb709c7527c1 694b5e6c47661fc447ef4a8ac1686c2986d034dc manjie007 <297867870@qq.com> 1716184049 +0000	commit: Detecting which pages have been accessed
diff --color -r ../../xv6-labs-2021/.git/logs/refs/heads/syscall xv6-labs-2021/.git/logs/refs/heads/syscall
1a2,3
> 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 manjie007 <297867870@qq.com> 1715611873 +0000	commit: system call trace
> 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 fbe7d4e93ef20a566c8cb9db4ae59abeca4e7a0f manjie007 <297867870@qq.com> 1715658098 +0000	commit: system call sysinfo
diff --color -r ../../xv6-labs-2021/.git/logs/refs/heads/util xv6-labs-2021/.git/logs/refs/heads/util
5a6
> bae676bbb85aa0f99ad21d59ae2e6bd174ee753e 288664627b747fc75e67a053eda795a7b6355800 manjie007 <297867870@qq.com> 1715327851 +0000	commit: add lab exercise fix xargs
Only in xv6-labs-2021/.git/objects: 01
Only in xv6-labs-2021/.git/objects: 0c
Only in xv6-labs-2021/.git/objects: 10
Only in xv6-labs-2021/.git/objects: 1c
Only in xv6-labs-2021/.git/objects/1e: 78a7b7a8248cdf561a3a7998e397a7c2d147b1
Only in xv6-labs-2021/.git/objects/1e: cc93f808887e6a7a186c6cc38c984affb76557
Only in xv6-labs-2021/.git/objects: 28
Only in xv6-labs-2021/.git/objects: 36
Only in xv6-labs-2021/.git/objects: 3a
Only in xv6-labs-2021/.git/objects: 3c
Only in xv6-labs-2021/.git/objects/4d: 72a7e132986988040119c76314ee30e142c223
Only in xv6-labs-2021/.git/objects/4d: cf110bdd48bc2edc8c193936fc953d34a714e6
Only in xv6-labs-2021/.git/objects: 63
Only in xv6-labs-2021/.git/objects: 65
Only in xv6-labs-2021/.git/objects: 66
Only in xv6-labs-2021/.git/objects: 69
Only in xv6-labs-2021/.git/objects: 6e
Only in xv6-labs-2021/.git/objects: 78
Only in xv6-labs-2021/.git/objects: 79
Only in xv6-labs-2021/.git/objects: 81
Only in xv6-labs-2021/.git/objects: 87
Only in xv6-labs-2021/.git/objects: 95
Only in xv6-labs-2021/.git/objects: 9c
Only in xv6-labs-2021/.git/objects: 9f
Only in xv6-labs-2021/.git/objects: a2
Only in xv6-labs-2021/.git/objects: a6
Only in xv6-labs-2021/.git/objects/b3: 518067f8fed673308305c8fc1c27255cbdf7f7
Only in xv6-labs-2021/.git/objects: b7
Only in xv6-labs-2021/.git/objects: bc
Only in xv6-labs-2021/.git/objects: c5
Only in xv6-labs-2021/.git/objects: c6
Only in xv6-labs-2021/.git/objects: cc
Only in xv6-labs-2021/.git/objects: cf
Only in xv6-labs-2021/.git/objects/e3: 07ea683c24312f184863196b5c804f4cb60f8a
Only in xv6-labs-2021/.git/objects: e4
Only in xv6-labs-2021/.git/objects: e5
Only in xv6-labs-2021/.git/objects: e8
Only in xv6-labs-2021/.git/objects: e9
Only in xv6-labs-2021/.git/objects: f3
Only in xv6-labs-2021/.git/objects: fb
Only in xv6-labs-2021/.git/objects: fd
Only in xv6-labs-2021/.git/objects: ff
diff --color -r ../../xv6-labs-2021/.git/refs/heads/pgtbl xv6-labs-2021/.git/refs/heads/pgtbl
1c1
< 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07
---
> 694b5e6c47661fc447ef4a8ac1686c2986d034dc
diff --color -r ../../xv6-labs-2021/.git/refs/heads/syscall xv6-labs-2021/.git/refs/heads/syscall
1c1
< 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af
---
> fbe7d4e93ef20a566c8cb9db4ae59abeca4e7a0f
diff --color -r ../../xv6-labs-2021/.git/refs/heads/util xv6-labs-2021/.git/refs/heads/util
1c1
< bae676bbb85aa0f99ad21d59ae2e6bd174ee753e
---
> 288664627b747fc75e67a053eda795a7b6355800
Only in ../../xv6-labs-2021: GPATH
Only in ../../xv6-labs-2021: GRTAGS
Only in ../../xv6-labs-2021: GTAGS
Only in xv6-labs-2021/__pycache__: gradelib.cpython-310.pyc
diff --color -r ../../xv6-labs-2021/kernel/defs.h xv6-labs-2021/kernel/defs.h
172a173,174
> void            vmprint(pagetable_t, int depth);
> pte_t*          walk(pagetable_t pagetable, uint64 va, int alloc);
diff --color -r ../../xv6-labs-2021/kernel/exec.c xv6-labs-2021/kernel/exec.c
118a119,120
>   if(p->pid==1) vmprint(p->pagetable, 1);
> 
diff --color -r ../../xv6-labs-2021/kernel/proc.c xv6-labs-2021/kernel/proc.c
198a199,217
>   // Map a read-only page for the process's system call data
>   uint64 pa = (uint64)kalloc();
>   if(pa == 0) {
>     //panic("bad kalloc in proc_pagetable\n");
>     uvmunmap(pagetable, TRAPFRAME, 1, 0);
>     uvmunmap(pagetable, TRAMPOLINE, 1, 0);
>     uvmfree(pagetable, 0);
>   }
>   memset((void*)pa, 0, PGSIZE);
>   struct usyscall *u = (struct usyscall*)pa;
>   u->pid = p->pid;
>   if(mappages(pagetable, USYSCALL, PGSIZE, pa, PTE_R | PTE_U) < 0){
>     kfree((void*)pa);
>     //panic("proc_pagetable: mappages");
>     uvmunmap(pagetable, TRAPFRAME, 1, 0);
>     uvmunmap(pagetable, TRAMPOLINE, 1, 0);
>     uvmfree(pagetable, 0);
>   }
> 
208a228
>   uvmunmap(pagetable, USYSCALL, 1, 1);
diff --color -r ../../xv6-labs-2021/kernel/riscv.h xv6-labs-2021/kernel/riscv.h
345a346
> #define PTE_A (1L << 6)  
diff --color -r ../../xv6-labs-2021/kernel/sysproc.c xv6-labs-2021/kernel/sysproc.c
78c78
< 
---
> //#define LAB_PGTBL
79a80,90
> /**
>  * Start by implementing sys_pgaccess() in kernel/sysproc.c.
>    You'll need to parse arguments using argaddr() and argint().
>    For the output bitmask, it's easier to store a temporary buffer in the kernel and copy it to the user (via copyout()) after filling it with the right bits.
>    It's okay to set an upper limit on the number of pages that can be scanned.
>    walk() in kernel/vm.c is very useful for finding the right PTEs.
>    You'll need to define PTE_A, the access bit, in kernel/riscv.h. Consult the RISC-V manual to determine its value.
>    Be sure to clear PTE_A after checking if it is set. Otherwise, it won't be possible to determine if the page was accessed since the last time pgaccess() was called (i.e., the bit will be set forever).
>    vmprint() may come in handy to debug page tables.
>  */
> #define MAX_PAGES 512
83c94,119
<   // lab pgtbl: your code here.
---
>   uint64 start_addr;
>   int num_pages;
>   uint64 bitmap;
>   pte_t *pte;
>   if(argaddr(0, &start_addr) < 0 || argint(1, &num_pages) < 0 || argaddr(2, &bitmap) < 0)
>     return -1;
>   
>   if(num_pages > MAX_PAGES) num_pages = MAX_PAGES;
> 
>   uint8 temp_bitmap[MAX_PAGES / 8];
>   memset(temp_bitmap, 0, sizeof(temp_bitmap));
> 
>   for(uint64 i = 0; i < num_pages; ++i) {
>     uint64 addr = start_addr + (i * PGSIZE);
>     pte = walk(myproc()->pagetable, addr, 0);
>     if (pte && (*pte & PTE_A)) {
>         temp_bitmap[i / 8] |= (1 << (i % 8));
>         *pte &= ~PTE_A;  // Clear the access bit
>     }
>   }
> 
>   //Copy the temporary bitmap to the user-provided buffer
>   if (copyout(myproc()->pagetable, (uint64)bitmap, (char *)temp_bitmap, num_pages / 8 + (num_pages % 8 ? 1 : 0)) < 0) {
>        return -1;
>   }
> 
diff --color -r ../../xv6-labs-2021/kernel/vm.c xv6-labs-2021/kernel/vm.c
434a435,458
> 
> void vmprint(pagetable_t pagetable, int depth) {
>   if (depth == 1) {
>     printf("page table %p\n", pagetable);
>   }
>   // there are 2^9 = 512 PTEs in a page table.
>   for (int i = 0; i < 512; i++) {
>     pte_t pte = pagetable[i];
>     if ((pte & PTE_V) && (pte & (PTE_R | PTE_W | PTE_X)) == 0) {
>       for (int j = 0; j < depth; ++j) {
>         printf("..");
>       }
>       printf(" %d: pte %p pa %p\n", i, pagetable[i], PTE2PA(pagetable[i]));
>       // this PTE points to a lower-level page table.
>       uint64 child = PTE2PA(pte);
>       vmprint((pagetable_t)child, depth + 1);
>     }else if(pte & PTE_V){
>       for (int j = 0; j < depth; ++j) {
>         printf("..");
>       }
>       printf(" %d: pte %p pa %p\n", i, pagetable[i], PTE2PA(pagetable[i]));
>     }
>   }
> }
Only in xv6-labs-2021: lab-pgtbl-handin.tar.gz
Only in xv6-labs-2021: lab-syscall-handin.tar.gz
Binary files ../../xv6-labs-2021/user/_find and xv6-labs-2021/user/_find differ
Binary files ../../xv6-labs-2021/user/_pingpong and xv6-labs-2021/user/_pingpong differ
Binary files ../../xv6-labs-2021/user/_primes and xv6-labs-2021/user/_primes differ
Binary files ../../xv6-labs-2021/user/_sleep and xv6-labs-2021/user/_sleep differ
Only in xv6-labs-2021/user: _sysinfotest
Only in xv6-labs-2021/user: _trace
Binary files ../../xv6-labs-2021/user/_xargs and xv6-labs-2021/user/_xargs differ
diff --color -r ../../xv6-labs-2021/xv6.out xv6-labs-2021/xv6.out
4d3
< hart 2 starting
5a5,16
> hart 2 starting
> page table 0x0000000087f6e000
> .. 0: pte 0x0000000021fda401 pa 0x0000000087f69000
> .... 0: pte 0x0000000021fda001 pa 0x0000000087f68000
> ...... 0: pte 0x0000000021fda81f pa 0x0000000087f6a000
> ...... 1: pte 0x0000000021fd9c0f pa 0x0000000087f67000
> ...... 2: pte 0x0000000021fd981f pa 0x0000000087f66000
> .. 255: pte 0x0000000021fdb401 pa 0x0000000087f6d000
> .... 511: pte 0x0000000021fdb001 pa 0x0000000087f6c000
> ...... 509: pte 0x0000000021fdac13 pa 0x0000000087f6b000
> ...... 510: pte 0x0000000021fddc07 pa 0x0000000087f77000
> ...... 511: pte 0x0000000020001c0b pa 0x0000000080007000
7,12c18,73
< $ sh < xargstest.sh
< $ echo DONE
< $ $ $ $ $ hello
< hello
< hello
< $ $ DONEqemu-system-riscv64: terminating on signal 15 from pid 93385 (<unknown process>)
---
> $ usertests
> usertests starting
> test MAXVAplus: usertrap(): unexpected scause 0x000000000000000f pid=6
>             sepc=0x0000000000002204 stval=0x0000004000000000
> usertrap(): unexpected scause 0x000000000000000f pid=7
>             sepc=0x0000000000002204 stval=0x0000008000000000
> usertrap(): unexpected scause 0x000000000000000f pid=8
>             sepc=0x0000000000002204 stval=0x0000010000000000
> usertrap(): unexpected scause 0x000000000000000f pid=9
>             sepc=0x0000000000002204 stval=0x0000020000000000
> usertrap(): unexpected scause 0x000000000000000f pid=10
>             sepc=0x0000000000002204 stval=0x0000040000000000
> usertrap(): unexpected scause 0x000000000000000f pid=11
>             sepc=0x0000000000002204 stval=0x0000080000000000
> usertrap(): unexpected scause 0x000000000000000f pid=12
>             sepc=0x0000000000002204 stval=0x0000100000000000
> usertrap(): unexpected scause 0x000000000000000f pid=13
>             sepc=0x0000000000002204 stval=0x0000200000000000
> usertrap(): unexpected scause 0x000000000000000f pid=14
>             sepc=0x0000000000002204 stval=0x0000400000000000
> usertrap(): unexpected scause 0x000000000000000f pid=15
>             sepc=0x0000000000002204 stval=0x0000800000000000
> usertrap(): unexpected scause 0x000000000000000f pid=16
>             sepc=0x0000000000002204 stval=0x0001000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=17
>             sepc=0x0000000000002204 stval=0x0002000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=18
>             sepc=0x0000000000002204 stval=0x0004000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=19
>             sepc=0x0000000000002204 stval=0x0008000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=20
>             sepc=0x0000000000002204 stval=0x0010000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=21
>             sepc=0x0000000000002204 stval=0x0020000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=22
>             sepc=0x0000000000002204 stval=0x0040000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=23
>             sepc=0x0000000000002204 stval=0x0080000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=24
>             sepc=0x0000000000002204 stval=0x0100000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=25
>             sepc=0x0000000000002204 stval=0x0200000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=26
>             sepc=0x0000000000002204 stval=0x0400000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=27
>             sepc=0x0000000000002204 stval=0x0800000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=28
>             sepc=0x0000000000002204 stval=0x1000000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=29
>             sepc=0x0000000000002204 stval=0x2000000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=30
>             sepc=0x0000000000002204 stval=0x4000000000000000
> usertrap(): unexpected scause 0x000000000000000f pid=31
>             sepc=0x0000000000002204 stval=0x8000000000000000
> OK
> test manywrites: qemu-system-riscv64: terminating on signal 2
