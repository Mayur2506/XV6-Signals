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

extern void start_sigret(void);
extern void end_sigret(void);

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
  p->tf->eip=(uint)p->sighandlers[signum];
  memmove(p->xyz,p->tf,sizeof(struct trapframe));
  uint sz;
  sz=(uint)end_sigret-(uint)start_sigret;
  p->tf->esp-=sz;
  memmove(p->tf->esp,start_sigret,sz);
  uint retaddress=p->tf->esp;
  p->tf->esp-=sizeof(uint);
  memmove((void *)p->tf->esp,(void *)retaddress,sizeof(uint));
  return;
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
