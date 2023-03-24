#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include <stddef.h>
#include "signal.h"


int
if_kern_sig(int signum)
{
  if( signum == SIGKILL || signum ==  SIGSTOP || signum == SIGCONT || signum == SIG_DFL)
    return 1;
  return 0;
}

int
sigdef(void)
{
    struct proc *p = myproc();
    if (p == 0)
        return -1;
    p->killed = 1;
    return 0;
}

int
sigcon(void)
{
    struct proc *p = myproc();
    if (p == 0 || p->state == RUNNING)
        return -1;
    p->stopped = 0;
    p->state = RUNNING;
    return 0;
}

int
sigterm(void)
{
  struct proc *p = myproc();
  if(p == 0)
    return -1;
  if(p->state == SLEEPING)
    p->state = RUNNABLE;
  p->killed = 1;
  return 0;
}

void
kern_handler(struct proc *p, int signum){
  if(signum == SIG_DFL){
    sigdef();
    return;
  }
  else if(signum == SIGCONT){
    sigcon();
    return;
  }
  else if(signum == SIGTERM){
    sigterm();
    return;
  }
}

void
user_handler(struct proc *p, int signum){
  
}

void
if_pending_sig(void)
{
  struct proc *p = myproc();
  int i;
  for(i = 0; i < NSIG; i++){
    if (p->pending_signals[i]){
        if(if_kern_sig(signum))
          kern_handler(p, signum);
        else{
          user_handler(p, signum);
        }
    }
  }
}