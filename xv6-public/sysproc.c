#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  // reading status input
  int status;
  if( argint(0, &status) < 0 ){
    return -1;
  }

  exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  int *p;
  
  if(argptr(0, (void*)&p, sizeof(int))<0){
    return -1;
  } 

  return wait(p);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
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

int
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

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// print hello world

int 
sys_helloWorld(void)
{
  cprintf("Hello World\n");
  return 0;
}


// return the number of open files by the current process

int
sys_numOpenFiles(void)
{

  int id;

  if(argint(0, &id) < 0) {
    cprintf("Illegal command or arguments\n");
    return -1;
  }

  // cprintf("Received ID: %d\n", id);
  

  return numOpenFiles(id);
}


int
sys_memAlloc(void)
{
  int id;

  if(argint(0, &id) < 0) {
    cprintf("Illegal command or arguments\n");
    return -1;
  }

  // cprintf("Received ID: %d\n", id);
  
  return memAlloc(id);
}

 
int
sys_getprocesstimedetails(void)
{
  int id;

  if(argint(0, &id) < 0) {
    cprintf("Illegal command or arguments\n");
    return -1;
  }

  // cprintf("Received ID: %d\n", id);

  return getprocesstimedetails(id);
  
}

int sys_psinfo(void) {
  psinfo();
  return 0;
}