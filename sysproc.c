#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "signal.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
   int pid;
   int signum;
   if(argint(0, &pid) < 0)
     return -1;
   if(argint(1, &signum) < 0)
     return -1;
   return kill(pid,signum);
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
  if_pending_sig();
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
int
sys_sigaction (void){
  int signum;
  void(*old)(void);
  void(*new)(void);
  if(argint(0, &signum) < 0)
    return -4;
  if(argptr(1, (void*)&new, sizeof(*new)) < 0)
    return -2;
  if(argptr(2, (void*)&old, sizeof(*old)) < 0)
    return -3;
  return sigaction(signum, new, old);
}
int
sys_sigret (void){
  int x=sigret();
  return x;
}
int
sys_pause (void){
  int x=pause();
  return x;
}
int
sys_sigmask(void){
   int sig,set,*old;
   if(argint(0,&sig) < 0){
      return -1;
   }
   if(argint(1,&set) < 0){
      return -1;
   }
   if(argptr(2,(void *)&old,sizeof(*old)) < 0){
      return -1;
   }
   return sigmask(sig,set,old);
}
