#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "date.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;


  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

//#define LAB_PGTBL
#ifdef LAB_PGTBL
/**
 * Start by implementing sys_pgaccess() in kernel/sysproc.c.
   You'll need to parse arguments using argaddr() and argint().
   For the output bitmask, it's easier to store a temporary buffer in the kernel and copy it to the user (via copyout()) after filling it with the right bits.
   It's okay to set an upper limit on the number of pages that can be scanned.
   walk() in kernel/vm.c is very useful for finding the right PTEs.
   You'll need to define PTE_A, the access bit, in kernel/riscv.h. Consult the RISC-V manual to determine its value.
   Be sure to clear PTE_A after checking if it is set. Otherwise, it won't be possible to determine if the page was accessed since the last time pgaccess() was called (i.e., the bit will be set forever).
   vmprint() may come in handy to debug page tables.
 */
#define MAX_PAGES 512
int
sys_pgaccess(void)
{
  uint64 start_addr;
  int num_pages;
  uint64 bitmap;
  pte_t *pte;
  if(argaddr(0, &start_addr) < 0 || argint(1, &num_pages) < 0 || argaddr(2, &bitmap) < 0)
    return -1;
  
  if(num_pages > MAX_PAGES) num_pages = MAX_PAGES;

  uint8 temp_bitmap[MAX_PAGES / 8];
  memset(temp_bitmap, 0, sizeof(temp_bitmap));

  for(uint64 i = 0; i < num_pages; ++i) {
    uint64 addr = start_addr + (i * PGSIZE);
    pte = walk(myproc()->pagetable, addr, 0);
    if (pte && (*pte & PTE_A)) {
        temp_bitmap[i / 8] |= (1 << (i % 8));
        *pte &= ~PTE_A;  // Clear the access bit
    }
  }

  //Copy the temporary bitmap to the user-provided buffer
  if (copyout(myproc()->pagetable, (uint64)bitmap, (char *)temp_bitmap, num_pages / 8 + (num_pages % 8 ? 1 : 0)) < 0) {
       return -1;
  }

  return 0;
}
#endif

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
