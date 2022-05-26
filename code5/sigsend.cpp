#include "signal.h" 
#include "unistd.h" 

#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 

int main(int argc,char**argv) 
{ 
pid_t pid; 
int signum; 
union sigval mysigval; 

signum=atoi(argv[1]); 
pid=(pid_t)atoi(argv[2]); 
mysigval.sival_int=8;//不代表具体含义，只用于说明问题 

if(sigqueue(pid,signum,mysigval)==-1) 
printf("send error\n"); 
sleep(2); 
} 
