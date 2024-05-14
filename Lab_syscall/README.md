diff --color -r ../../xv6-labs-2021/.git/COMMIT_EDITMSG xv6-labs-2021/.git/COMMIT_EDITMSG
1c1
< add lab exercise 1 xargs
---
> system call sysinfo
diff --color -r ../../xv6-labs-2021/.git/FETCH_HEAD xv6-labs-2021/.git/FETCH_HEAD
1c1
< f654383cdec479c9d53a02bffa1ab5526f6c3ca4		branch 'util' of git://g.csail.mit.edu/xv6-labs-2021
---
> 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af		branch 'syscall' of git://g.csail.mit.edu/xv6-labs-2021
9d8
< 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af	not-for-merge	branch 'syscall' of git://g.csail.mit.edu/xv6-labs-2021
11a11
> f654383cdec479c9d53a02bffa1ab5526f6c3ca4	not-for-merge	branch 'util' of git://g.csail.mit.edu/xv6-labs-2021
Only in xv6-labs-2021/.git: ORIG_HEAD
Binary files ../../xv6-labs-2021/.git/index and xv6-labs-2021/.git/index differ
diff --color -r ../../xv6-labs-2021/.git/logs/HEAD xv6-labs-2021/.git/logs/HEAD
6a7,12
> 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af bae676bbb85aa0f99ad21d59ae2e6bd174ee753e manjie007 <297867870@qq.com> 1715325821 +0000	checkout: moving from syscall to util
> bae676bbb85aa0f99ad21d59ae2e6bd174ee753e 288664627b747fc75e67a053eda795a7b6355800 manjie007 <297867870@qq.com> 1715327851 +0000	commit: add lab exercise fix xargs
> 288664627b747fc75e67a053eda795a7b6355800 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af manjie007 <297867870@qq.com> 1715327856 +0000	checkout: moving from util to syscall
> 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 manjie007 <297867870@qq.com> 1715611873 +0000	commit: system call trace
> 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 MANJIE007 <297867870@qq.com> 1715657468 +0800	reset: moving to HEAD
> 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 2c6e1946fc554b95111de242326e1aa91bdd497b MANJIE007 <297867870@qq.com> 1715657477 +0800	commit: system call sysinfo
diff --color -r ../../xv6-labs-2021/.git/logs/refs/heads/syscall xv6-labs-2021/.git/logs/refs/heads/syscall
1a2,3
> 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 manjie007 <297867870@qq.com> 1715611873 +0000	commit: system call trace
> 1e78a7b7a8248cdf561a3a7998e397a7c2d147b1 2c6e1946fc554b95111de242326e1aa91bdd497b MANJIE007 <297867870@qq.com> 1715657477 +0800	commit: system call sysinfo
diff --color -r ../../xv6-labs-2021/.git/logs/refs/heads/util xv6-labs-2021/.git/logs/refs/heads/util
5a6
> bae676bbb85aa0f99ad21d59ae2e6bd174ee753e 288664627b747fc75e67a053eda795a7b6355800 manjie007 <297867870@qq.com> 1715327851 +0000	commit: add lab exercise fix xargs
Only in xv6-labs-2021/.git/objects: 01
Only in xv6-labs-2021/.git/objects: 1c
Only in xv6-labs-2021/.git/objects/1e: 78a7b7a8248cdf561a3a7998e397a7c2d147b1
Only in xv6-labs-2021/.git/objects/1e: cc93f808887e6a7a186c6cc38c984affb76557
Only in xv6-labs-2021/.git/objects: 28
Only in xv6-labs-2021/.git/objects: 2c
Only in xv6-labs-2021/.git/objects: 3a
Only in xv6-labs-2021/.git/objects/4d: 72a7e132986988040119c76314ee30e142c223
Only in xv6-labs-2021/.git/objects/4d: cf110bdd48bc2edc8c193936fc953d34a714e6
Only in xv6-labs-2021/.git/objects: 63
Only in xv6-labs-2021/.git/objects: 66
Only in xv6-labs-2021/.git/objects: 78
Only in xv6-labs-2021/.git/objects: 79
Only in xv6-labs-2021/.git/objects: 81
Only in xv6-labs-2021/.git/objects: 87
Only in xv6-labs-2021/.git/objects: 95
Only in xv6-labs-2021/.git/objects: 9c
Only in xv6-labs-2021/.git/objects: a6
Only in xv6-labs-2021/.git/objects: bc
Only in xv6-labs-2021/.git/objects: c5
Only in xv6-labs-2021/.git/objects: c6
Only in xv6-labs-2021/.git/objects: cc
Only in xv6-labs-2021/.git/objects: cf
Only in xv6-labs-2021/.git/objects: e4
Only in xv6-labs-2021/.git/objects: e5
Only in xv6-labs-2021/.git/objects: e8
Only in xv6-labs-2021/.git/objects: fd
Only in xv6-labs-2021/.git/objects: ff
diff --color -r ../../xv6-labs-2021/.git/refs/heads/syscall xv6-labs-2021/.git/refs/heads/syscall
1c1
< 1e6e6cafbb26a898b8c3f90e819fc5e7227dc8af
---
> 2c6e1946fc554b95111de242326e1aa91bdd497b
diff --color -r ../../xv6-labs-2021/.git/refs/heads/util xv6-labs-2021/.git/refs/heads/util
1c1
< bae676bbb85aa0f99ad21d59ae2e6bd174ee753e
---
> 288664627b747fc75e67a053eda795a7b6355800
Only in ../../xv6-labs-2021: GPATH
Only in ../../xv6-labs-2021: GRTAGS
Only in ../../xv6-labs-2021: GTAGS
diff --color -r ../../xv6-labs-2021/Makefile xv6-labs-2021/Makefile
195a196,197
> 	$U/_trace\
> 	$U/_sysinfotest\
Only in xv6-labs-2021/__pycache__: gradelib.cpython-310.pyc
diff --color -r ../../xv6-labs-2021/kernel/defs.h xv6-labs-2021/kernel/defs.h
65a66
> uint64          freemem(void);
106a108
> int             nproc(void);
diff --color -r ../../xv6-labs-2021/kernel/kalloc.c xv6-labs-2021/kernel/kalloc.c
82a83,96
> 
> // 获取空闲内存总量
> uint64 freemem(void) {
>   uint64 count = 0;
>   struct run *r;
> 
>   acquire(&kmem.lock); // 加锁
>   for (r = kmem.freelist; r != 0; r = r->next) {
>     count += PGSIZE; // 每个空闲页大小为 PGSIZE
>   }
>   release(&kmem.lock); // 释放锁
> 
>   return count;
> }
diff --color -r ../../xv6-labs-2021/kernel/proc.c xv6-labs-2021/kernel/proc.c
122a123,125
>   //set up trace_mask
>   p->trace_mask = 0;
> 
307a311,313
>   //add trace_mask
>   np->trace_mask = p->trace_mask;
> 
656a663,680
> 
> int
> nproc(void)
> {
>     int count = 0;
>     struct proc *p;
> 
>     for(p = proc; p < &proc[NPROC]; p++) {
>       acquire(&p->lock);
>       if(p->state != UNUSED) {
>         count++;
>       }
>       release(&p->lock);
>     }
> 
>     return count;
> }
> 
diff --color -r ../../xv6-labs-2021/kernel/proc.h xv6-labs-2021/kernel/proc.h
94a95
>   int trace_mask;                     // trace_arg
diff --color -r ../../xv6-labs-2021/kernel/syscall.c xv6-labs-2021/kernel/syscall.c
106a107,108
> extern uint64 sys_trace(void);
> extern uint64 sys_sysinfo(void);
129a132,133
> [SYS_trace]   sys_trace,
> [SYS_sysinfo] sys_sysinfo,
131a136,161
> static const char* syscall_names[] = {
> [SYS_fork]    "fork",
> [SYS_exit]    "exit",
> [SYS_wait]    "wait",
> [SYS_pipe]    "pipe",
> [SYS_read]    "read",
> [SYS_kill]    "kill",
> [SYS_exec]    "exec",
> [SYS_fstat]   "fstat",
> [SYS_chdir]   "chdir",
> [SYS_dup]     "dup",
> [SYS_getpid]  "getpid",
> [SYS_sbrk]    "sbrk",
> [SYS_sleep]   "sleep",
> [SYS_uptime]  "uptime",
> [SYS_open]    "open",
> [SYS_write]   "write",
> [SYS_mknod]   "mknod",
> [SYS_unlink]  "unlink",
> [SYS_link]    "link",
> [SYS_mkdir]   "mkdir",
> [SYS_close]   "close",
> [SYS_trace]   "trace",
> [SYS_sysinfo] "sysinfo",
> };
> 
140c170,176
<     p->trapframe->a0 = syscalls[num]();
---
>     //p->trapframe->a0 = syscalls[num]();
>     uint64 res;
>     res = syscalls[num]();
>     p->trapframe->a0 = res;
>     if (p->trace_mask & (1 << num)) {
>       printf("%d: syscall %s -> %d\n", p->pid, syscall_names[num], res);
>     }
diff --color -r ../../xv6-labs-2021/kernel/syscall.h xv6-labs-2021/kernel/syscall.h
22a23,24
> #define SYS_trace  22
> #define SYS_sysinfo  23
diff --color -r ../../xv6-labs-2021/kernel/sysproc.c xv6-labs-2021/kernel/sysproc.c
8a9
> #include "sysinfo.h"
96a98,130
> }
> 
> uint64
> sys_trace(void)
> {
>   int n;
>   if(argint(0, &n) < 0)
>     return -1;
>   
>   struct proc *p = myproc();
>   acquire(&p->lock);
>   p->trace_mask = n;
>   release(&p->lock);
> 
>   return 0;  // not reached
> }
> 
> uint64
> sys_sysinfo(void)
> {
>   uint64 p;
>   if(argaddr(0, &p) < 0)
>     return -1;
>   
>   struct proc *mp = myproc();
>   struct sysinfo si;
> 
>   si.freemem = freemem();
>   si.nproc = nproc();
> 
>   if(copyout(mp->pagetable, p, (char *)&si, sizeof(si)) < 0)
>     return -1;
>   return 0;
Binary files ../../xv6-labs-2021/user/_find and xv6-labs-2021/user/_find differ
Binary files ../../xv6-labs-2021/user/_pingpong and xv6-labs-2021/user/_pingpong differ
Binary files ../../xv6-labs-2021/user/_primes and xv6-labs-2021/user/_primes differ
Binary files ../../xv6-labs-2021/user/_sleep and xv6-labs-2021/user/_sleep differ
Binary files ../../xv6-labs-2021/user/_xargs and xv6-labs-2021/user/_xargs differ
diff --color -r ../../xv6-labs-2021/user/user.h xv6-labs-2021/user/user.h
0a1,2
> #include "../kernel/types.h"
> 
25a28,30
> int trace(int);
> struct sysinfo;
> int sysinfo(struct sysinfo *);
diff --color -r ../../xv6-labs-2021/user/usys.pl xv6-labs-2021/user/usys.pl
38a39,40
> entry("trace");
> entry("sysinfo");
diff --color -r ../../xv6-labs-2021/xv6.out xv6-labs-2021/xv6.out
4d3
< hart 2 starting
5a5
> hart 2 starting
7,12c7,10
< $ sh < xargstest.sh
< $ echo DONE
< $ $ $ $ $ hello
< hello
< hello
< $ $ DONEqemu-system-riscv64: terminating on signal 15 from pid 93385 (<unknown process>)
---
> $ sysinfotest
> sysinfotest: start
> sysinfotest: OK
> $ qemu-system-riscv64: terminating on signal 15 from pid 4178 (make)
