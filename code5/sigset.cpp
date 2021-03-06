#include "signal.h" 
#include "unistd.h" 

#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 

using namespace std;

static void my_op(int); 
int main() 
{ 
sigset_t new_mask,old_mask,pending_mask; 
struct sigaction act; 

sigemptyset(&act.sa_mask); 
act.sa_flags=SA_SIGINFO; //设此标志后参数才可以传递给信号处理函数
act.sa_handler=my_op; 
if(sigaction(SIGALRM,&act,NULL)) //SIGRTMIN+10
	printf("install signal SIGALRM error\n"); 

//cout<<"The pid is "<<getpid()<<endl;
alarm(1);
//sleep(10);
sigemptyset(&new_mask); 
sigaddset(&new_mask,SIGALRM); 
if(sigprocmask(SIG_BLOCK, &new_mask,&old_mask)) 
	printf("block signal SIGALRM error\n"); 

cout<<"SIGALRM is set blocked"<<endl;
cout<<"Sleep 10s"<<endl;
sleep(10); 
printf("now begin to get pending mask and unblock SIGALRM\n"); 

if(sigpending(&pending_mask)<0) 
	printf("get pending mask error\n"); 

if(sigismember(&pending_mask,SIGALRM)) 
	printf("signal SIGALRM is pending\n"); 

if(sigprocmask(SIG_SETMASK,&old_mask,NULL)<0) 
	printf("unblock signal error\n"); 
printf("signal unblocked\n"); 

cout<<"Sleep 10s"<<endl;
//alarm(1);
sleep(10); 
} 

static void my_op(int signum) 
{ 
printf("receive signal %d \n",signum); 
} 
