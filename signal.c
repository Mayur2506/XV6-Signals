#include "types.h"
#include "stat.h"
#include "user.h"
#include "signal.h"
#include "param.h"
#include "fcntl.h"
#include <stddef.h>
void tp(){
  printf(1,"In SIG_IGN user defined function\n");
}
void user(){
   printf(1,"In SIGCONT user defined function\n");
}
void sigtest(){
  int pid;
  pid = fork();
  if (pid == 0) {
    printf(1, "Sending SIGSTOP signal to child process\n");
    kill(pid, SIGSTOP);
    sleep(100);
    printf(1,"child process resumed\n");
    while(1){
      printf(1,"child process running\n");
      sleep(10);
    }
    exit();
  }
  else
  {
    sleep(100);
    printf(1, "Sending SIGCONT signal to child process\n");
    kill(pid, SIGCONT);
    sleep(500);
    printf(1,"Terminating child Process\n");
    kill(pid,SIGKILL);
    wait();
    printf(1,"Sigstop,sigcont working\n");
  }
}
void pauset()
{
  int pid = fork();
  if (pid == 0) {
    printf(1, "Child process pausing...\n");
    pause();
    printf(1, "Child process resumed!\n");
     exit();
  } else {
    sleep(100);
    printf(1, "Sending SIG_IGN signal to Child Process\n");
    kill(pid,SIG_IGN);
    sleep(100);
    printf(1,"Terminating child Process\n");
    kill(pid,SIGKILL);
    wait();
  }
  printf(1,"pause working\n");
}
void sigprocmasktest(){
   int pid;
  pid = fork();
  if (pid == 0){
    printf(1,"child process resumed\n");
    while(1){
      printf(1,"child process running\n");
      sleep(10);
    }
    exit();
  }
  else
  {
    sleep(100);
    printf(1, "Sending SIGSTOP signal to child process\n");
    kill(pid, SIGSTOP);
    sleep(300);
    printf(1, "Sending SIGCONT signal to child process\n");
    kill(pid, SIGCONT);
    sleep(100);
    sleep(100);
    kill(pid,SIGKILL);
    wait();
    printf(1,"Sigstop,sigcont working\n");
  }
}
void userhandler(){
  int pid;
  pid=fork();
  if (pid == 0) {
    printf(1,"Defined User function for sigcont\n");
    sigaction(SIGCONT,user,NULL);
    printf(1,"Defined User function for sigcont\n");
    sigaction(SIG_IGN,tp,NULL);
    while(1) {
      continue;
    }
    exit();
  }
  else
  {
    sleep(100);
    printf(1,"Sending sigcont signal\n");
    kill(pid,SIGCONT);
    sleep(100);
    printf(1,"Sending sigint signal\n");
    kill(pid,SIG_IGN);
    sleep(100);
    kill(pid,SIGKILL);
    wait();
  }
  printf(1,"User Handler Test working\n");
}
int main(){
  sigtest();
  pauset();
  sigprocmasktest();
  userhandler();
  exit();
}
