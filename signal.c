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
  if(signum == SIGTERM){
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
  for(i = 0; i < MAXSIGNALS; i++){
    if (p->pending[i]){
        if(p->sighandlers[i]==SIG_DFL)
          kern_handler(p, i);
        else{
          user_handler(p, i);
        }
    }
  }
}
