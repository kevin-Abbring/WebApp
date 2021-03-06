#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 

int main()
{
	struct sigaction act,oldact;
	int i;
	act.sa_handler=SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	if(sigaction(SIGCHLD,&act,&oldact)<0){
		printf("sigaction error.");
		exit(1);
	}
	for(i=0;i<5;i++)
		if(fork()==0)
			exit(0);
	for(;;){}
}
