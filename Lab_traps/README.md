diff --color -r ../../xv6-labs-2021/.git/COMMIT_EDITMSG xv6-labs-2021/.git/COMMIT_EDITMSG
1c1
< add lab exercise 1 xargs
---
> Alarm
diff --color -r ../../xv6-labs-2021/.git/FETCH_HEAD xv6-labs-2021/.git/FETCH_HEAD
1c1
< f654383cdec479c9d53a02bffa1ab5526f6c3ca4		branch 'util' of git://g.csail.mit.edu/xv6-labs-2021
---
> 219a8d7d70b6ac66b1447aeada079a1f8c3027f7		branch 'traps' of git://g.csail.mit.edu/xv6-labs-2021
11c11
< 219a8d7d70b6ac66b1447aeada079a1f8c3027f7	not-for-merge	branch 'traps' of git://g.csail.mit.edu/xv6-labs-2021
---
> f654383cdec479c9d53a02bffa1ab5526f6c3ca4	not-for-merge	branch 'util' of git://g.csail.mit.edu/xv6-labs-2021
Binary files ../../xv6-labs-2021/.git/index and xv6-labs-2021/.git/index differ
diff --color -r ../../xv6-labs-2021/.git/logs/HEAD xv6-labs-2021/.git/logs/HEAD
7,8c7,21
< 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07 MANJIE007 <297867870@qq.com> 1716184392 +0800	checkout: moving from syscall to pgtbl
< 1e6b2dec7d5ca49571e426ccc6cd686d009b6d07 219a8d7d70b6ac66b1447aeada079a1f8c3027f7 MANJIE007 <297867870@qq.com> 1717170075 +0800	checkout: moving from pgtbl to traps
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
> 694b5e6c47661fc447ef4a8ac1686c2986d034dc 219a8d7d70b6ac66b1447aeada079a1f8c3027f7 manjie007 <297867870@qq.com> 1716548904 +0000	checkout: moving from pgtbl to traps
> 219a8d7d70b6ac66b1447aeada079a1f8c3027f7 694b5e6c47661fc447ef4a8ac1686c2986d034dc manjie007 <297867870@qq.com> 1716648446 +0000	checkout: moving from traps to pgtbl
> 694b5e6c47661fc447ef4a8ac1686c2986d034dc 219a8d7d70b6ac66b1447aeada079a1f8c3027f7 manjie007 <297867870@qq.com> 1716814271 +0000	checkout: moving from pgtbl to traps
> 219a8d7d70b6ac66b1447aeada079a1f8c3027f7 4434ff90b6924079f40129fef87534f6e785e3a3 manjie007 <297867870@qq.com> 1716970399 +0000	commit: RISC-V assembly
> 4434ff90b6924079f40129fef87534f6e785e3a3 50e7e8f611b336e9e630f6671d66f97cea364e2d manjie007 <297867870@qq.com> 1716972998 +0000	commit: Backtrace
> 50e7e8f611b336e9e630f6671d66f97cea364e2d 0b04a2a90d64d95b4f7938936757c8e43a3866cf manjie007 <297867870@qq.com> 1717169863 +0000	commit: Alarm
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
diff --color -r ../../xv6-labs-2021/.git/logs/refs/heads/traps xv6-labs-2021/.git/logs/refs/heads/traps
1c1,4
< 0000000000000000000000000000000000000000 219a8d7d70b6ac66b1447aeada079a1f8c3027f7 MANJIE007 <297867870@qq.com> 1717170075 +0800	branch: Created from refs/remotes/origin/traps
---
> 0000000000000000000000000000000000000000 219a8d7d70b6ac66b1447aeada079a1f8c3027f7 manjie007 <297867870@qq.com> 1716548904 +0000	branch: Created from refs/remotes/origin/traps
> 219a8d7d70b6ac66b1447aeada079a1f8c3027f7 4434ff90b6924079f40129fef87534f6e785e3a3 manjie007 <297867870@qq.com> 1716970399 +0000	commit: RISC-V assembly
> 4434ff90b6924079f40129fef87534f6e785e3a3 50e7e8f611b336e9e630f6671d66f97cea364e2d manjie007 <297867870@qq.com> 1716972998 +0000	commit: Backtrace
> 50e7e8f611b336e9e630f6671d66f97cea364e2d 0b04a2a90d64d95b4f7938936757c8e43a3866cf manjie007 <297867870@qq.com> 1717169863 +0000	commit: Alarm
diff --color -r ../../xv6-labs-2021/.git/logs/refs/heads/util xv6-labs-2021/.git/logs/refs/heads/util
5a6
> bae676bbb85aa0f99ad21d59ae2e6bd174ee753e 288664627b747fc75e67a053eda795a7b6355800 manjie007 <297867870@qq.com> 1715327851 +0000	commit: add lab exercise fix xargs
Only in xv6-labs-2021/.git/objects: 01
Only in xv6-labs-2021/.git/objects: 08
Only in xv6-labs-2021/.git/objects: 0b
Only in xv6-labs-2021/.git/objects: 0c
Only in xv6-labs-2021/.git/objects: 0e
Only in xv6-labs-2021/.git/objects: 10
Only in xv6-labs-2021/.git/objects: 16
Only in xv6-labs-2021/.git/objects: 1c
Only in xv6-labs-2021/.git/objects/1e: 78a7b7a8248cdf561a3a7998e397a7c2d147b1
Only in xv6-labs-2021/.git/objects/1e: cc93f808887e6a7a186c6cc38c984affb76557
Only in xv6-labs-2021/.git/objects: 24
Only in xv6-labs-2021/.git/objects: 28
Only in xv6-labs-2021/.git/objects: 36
Only in xv6-labs-2021/.git/objects: 3a
Only in xv6-labs-2021/.git/objects: 3c
Only in xv6-labs-2021/.git/objects: 44
Only in xv6-labs-2021/.git/objects/4d: 72a7e132986988040119c76314ee30e142c223
Only in xv6-labs-2021/.git/objects/4d: cf110bdd48bc2edc8c193936fc953d34a714e6
Only in xv6-labs-2021/.git/objects: 4f
Only in xv6-labs-2021/.git/objects: 50
Only in xv6-labs-2021/.git/objects: 63
Only in xv6-labs-2021/.git/objects: 64
Only in xv6-labs-2021/.git/objects: 65
Only in xv6-labs-2021/.git/objects: 66
Only in xv6-labs-2021/.git/objects: 69
Only in xv6-labs-2021/.git/objects: 6e
Only in xv6-labs-2021/.git/objects: 78
Only in xv6-labs-2021/.git/objects: 79
Only in xv6-labs-2021/.git/objects: 7b
Only in xv6-labs-2021/.git/objects: 81
Only in xv6-labs-2021/.git/objects: 87
Only in xv6-labs-2021/.git/objects: 90
Only in xv6-labs-2021/.git/objects: 92
Only in xv6-labs-2021/.git/objects: 95
Only in xv6-labs-2021/.git/objects: 98
Only in xv6-labs-2021/.git/objects: 9c
Only in xv6-labs-2021/.git/objects: 9f
Only in xv6-labs-2021/.git/objects: a0
Only in xv6-labs-2021/.git/objects: a2
Only in xv6-labs-2021/.git/objects: a6
Only in xv6-labs-2021/.git/objects: a7
Only in xv6-labs-2021/.git/objects: a9
Only in xv6-labs-2021/.git/objects/b3: 518067f8fed673308305c8fc1c27255cbdf7f7
Only in xv6-labs-2021/.git/objects: b7
Only in xv6-labs-2021/.git/objects: bc
Only in xv6-labs-2021/.git/objects: c5
Only in xv6-labs-2021/.git/objects: c6
Only in xv6-labs-2021/.git/objects: cc
Only in xv6-labs-2021/.git/objects: cf
Only in xv6-labs-2021/.git/objects: d5
Only in xv6-labs-2021/.git/objects: d7
Only in xv6-labs-2021/.git/objects/e3: 07ea683c24312f184863196b5c804f4cb60f8a
Only in xv6-labs-2021/.git/objects: e4
Only in xv6-labs-2021/.git/objects: e5
Only in xv6-labs-2021/.git/objects: e8
Only in xv6-labs-2021/.git/objects: e9
Only in xv6-labs-2021/.git/objects: ed
Only in xv6-labs-2021/.git/objects: f3
Only in xv6-labs-2021/.git/objects: fa
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
diff --color -r ../../xv6-labs-2021/.git/refs/heads/traps xv6-labs-2021/.git/refs/heads/traps
1c1
< 219a8d7d70b6ac66b1447aeada079a1f8c3027f7
---
> 0b04a2a90d64d95b4f7938936757c8e43a3866cf
diff --color -r ../../xv6-labs-2021/.git/refs/heads/util xv6-labs-2021/.git/refs/heads/util
1c1
< bae676bbb85aa0f99ad21d59ae2e6bd174ee753e
---
> 288664627b747fc75e67a053eda795a7b6355800
Only in ../../xv6-labs-2021: GPATH
Only in ../../xv6-labs-2021: GRTAGS
Only in ../../xv6-labs-2021: GTAGS
diff --color -r ../../xv6-labs-2021/Makefile xv6-labs-2021/Makefile
190a191
> 	$U/_alarmtest\
Only in xv6-labs-2021/__pycache__: gradelib.cpython-310.pyc
Only in xv6-labs-2021: answers-traps.txt
diff --color -r ../../xv6-labs-2021/kernel/defs.h xv6-labs-2021/kernel/defs.h
82a83
> void            backtrace(void);
diff --color -r ../../xv6-labs-2021/kernel/printf.c xv6-labs-2021/kernel/printf.c
123a124
>   backtrace();
133a135,147
> }
> 
> void
> backtrace(void)
> {
>   uint64 fp = r_fp();
>   printf("backtrace:\n");
> 
>   while (fp != 0 && fp >= PGROUNDDOWN(fp) && fp < PGROUNDUP(fp)) {
>     uint64 return_address = *(uint64 *)(fp - 8);
>     printf("%p\n", return_address);
>     fp = *(uint64 *)(fp - 16);
>   }
diff --color -r ../../xv6-labs-2021/kernel/proc.c xv6-labs-2021/kernel/proc.c
122a123,125
>   p->alarmticks = 0;
>   p->alarmremain = 0;
>   p->alarmhandler = 0;
123a127,133
>   if((p->original_trapframe = (struct trapframe *)kalloc()) == 0){
>     freeproc(p);
>     release(&p->lock);
>     return 0;
>   }
> 
>   // Allocate a trapframe page.
152a163,164
>   if(p->original_trapframe)
>     kfree((void*)p->original_trapframe);
166a179,181
>   p->alarmticks = 0;
>   p->alarmremain = 0;
>   p->alarmhandler = 0;
diff --color -r ../../xv6-labs-2021/kernel/proc.h xv6-labs-2021/kernel/proc.h
95a96,100
>   int alarmticks;              //Interval for the alarm
>   int alarmremain;             //Ticks remaining unitl the next alarm
>   void (*alarmhandler)();     //alarm handler
>   struct trapframe *original_trapframe;  
> 
diff --color -r ../../xv6-labs-2021/kernel/riscv.h xv6-labs-2021/kernel/riscv.h
366a367,374
> 
> static inline uint64
> r_fp()
> {
>   uint64 x;
>   asm volatile("mv %0, s0" : "=r" (x) );
>   return x;
> }
diff --color -r ../../xv6-labs-2021/kernel/syscall.c xv6-labs-2021/kernel/syscall.c
106a107,108
> extern uint64 sys_sigalarm(void);
> extern uint64 sys_sigreturn(void);
129a132,133
> [SYS_sigalarm]   sys_sigalarm,
> [SYS_sigreturn]   sys_sigreturn,
diff --color -r ../../xv6-labs-2021/kernel/syscall.h xv6-labs-2021/kernel/syscall.h
22a23,24
> #define SYS_sigalarm  22
> #define SYS_sigreturn  23
diff --color -r ../../xv6-labs-2021/kernel/sysproc.c xv6-labs-2021/kernel/sysproc.c
62a63,66
> 
>   //add
>   backtrace();
> 
96a101,128
> }
> 
> uint64
> sys_sigalarm(void)
> {
>   int ticks;
>   uint64 handler;
>   
>   if (argint(0, &ticks) < 0 || argaddr(1, &handler) < 0) 
>     return -1;
>   
>   struct proc *p = myproc();
>   acquire(&p->lock);
>   p->alarmticks = ticks;
>   p->alarmremain = ticks;
>   p->alarmhandler = (void(*)()) handler;
>   release(&p->lock);
> 
>   return 0;
> }
> 
> uint64
> sys_sigreturn(void)
> {
>   struct proc *p = myproc();
>   p->alarmremain = p->alarmticks;
>   *p->trapframe = *p->original_trapframe;
>   return 0;
diff --color -r ../../xv6-labs-2021/kernel/trap.c xv6-labs-2021/kernel/trap.c
80c80,88
<   if(which_dev == 2)
---
>   if(which_dev == 2) {
>     if (p->alarmticks) {
>       if (p->alarmremain == 0) {
>         //p->alarmremain = p->alarmticks;
>         *p->original_trapframe = *p->trapframe;
>         p->trapframe->epc = (uint64)p->alarmhandler;
>       }
>       p->alarmremain--;
>     }
81a90
>   }
Only in xv6-labs-2021: lab-pgtbl-handin.tar.gz
Only in xv6-labs-2021: lab-syscall-handin.tar.gz
Only in xv6-labs-2021: lab-traps-handin.tar.gz
Binary files ../../xv6-labs-2021/user/_find and xv6-labs-2021/user/_find differ
Only in xv6-labs-2021/user: _pgtbltest
Binary files ../../xv6-labs-2021/user/_pingpong and xv6-labs-2021/user/_pingpong differ
Binary files ../../xv6-labs-2021/user/_primes and xv6-labs-2021/user/_primes differ
Binary files ../../xv6-labs-2021/user/_sleep and xv6-labs-2021/user/_sleep differ
Only in xv6-labs-2021/user: _sysinfotest
Only in xv6-labs-2021/user: _trace
Binary files ../../xv6-labs-2021/user/_xargs and xv6-labs-2021/user/_xargs differ
diff --color -r ../../xv6-labs-2021/user/user.h xv6-labs-2021/user/user.h
25a26,27
> int sigalarm(int, void(*)());
> int sigreturn(void);
diff --color -r ../../xv6-labs-2021/user/usys.pl xv6-labs-2021/user/usys.pl
38a39,40
> entry("sigalarm");
> entry("sigreturn");
diff --color -r ../../xv6-labs-2021/xv6.out xv6-labs-2021/xv6.out
4d3
< hart 2 starting
5a5
> hart 2 starting
7,12c7,63
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
> test manywrites: OK
> test execout: qemu-system-riscv64: terminating on signal 2
