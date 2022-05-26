#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include<stdlib.h> 
#include<errno.h> 

void sigchld_handler(int);

int main()
{
	struct sigaction act;
	int i;
	act.sa_handler=sigchld_handler;
	sigemptyset(&act.sa_mask);
	if(sigaction(SIGCHLD,&act,NULL)<0){
		printf("sigaction error.");
		exit(1);
	}
	for(i=0;i<5;i++){
		if(fork()==0){
			printf("child %d\n",getpid());
			exit(0);
		}		
	}
	for(;;){}
}

void sigchld_handler(int sig)
{
	pid_t pid;
	int stat;
	for(;(pid=waitpid(-1,&stat,WNOHANG))>0;)
	{
		printf("child %d died:%d\n",pid,WEXITSTATUS(stat));
	}
}
