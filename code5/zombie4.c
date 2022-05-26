#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 

int main()
{
	int i;
	pid_t pid;
	pid=fork();
	if(pid==0){
		//子进程1
		printf("first child proc:%d\n",getpid());
		for(i=0;i<5;i++)
		{
			if(fork()==0){
				//子进程2，3，4，5，6
				printf("child %d\n",getpid());
				sleep(1);
				exit(0);
			}
		}
		exit(0);
	}
	for(;;){}
}
