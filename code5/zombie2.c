#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 

int main()
{
	int i,stat;
	pid_t pid;
	for(i=0;i<5;i++){
		if(fork()==0){
			printf("child %d\n",getpid());
			exit(0);
		}
	}
	for(;(pid=wait(&stat))>0;){
		printf("child %d died:%d\n",pid,WEXITSTATUS(stat));
	}
}
