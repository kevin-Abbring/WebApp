#include "signal.h" 
#include "unistd.h" 

#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 

void new_op(int); 
int main(int argc,char**argv) 
{ 
struct sigaction act; 
int sig; 
sig=atoi(argv[1]); 

sigemptyset(&act.sa_mask); 
act.sa_flags=SA_SIGINFO; 
act.sa_handler=new_op; 

if(sigaction(sig,&act,NULL) < 0) 
{ 
printf("install sigal error\n"); 
} 

printf("The pid is %d\n",getpid());

while(1) 
{ 
printf("wait for the signal\n"); 
sleep(10); 
} 
} 
void new_op(int signum) 
{ 
printf("receive signal %d", signum); 
sleep(5); 
} 
