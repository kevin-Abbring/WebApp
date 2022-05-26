#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h> 

#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

using namespace std;

int main(int argc,char **argv)
{
	pid_t pid;
	int n=atoi(argv[1]);

	for(int i=0;i<n;i++)
	{	
		pid=fork();
		if(pid==0)	//子进程程序
		{
			cout<<"child process:ppid="<<getppid()<<",pid="<<getpid()<<endl;
			for(int j=0;j<10;j++){			
				sleep(1);
				cout<<"I am child "<<getpid()<<endl;
				cout<<"		I have "<<9-j<<"second left"<<endl;
			}
			exit(0);
		}
		else if(pid>0)	//父进程程序
		{
			cout<<"parent process:ppid="<<getppid()<<",pid="<<getpid()<<endl;
			sleep(1);
		}
		else	//调用失败
			cout<<"create child process fail"<<endl;
	}
	sleep(60);
//	for(int i=0;i<5;i++)
//		wait();	

	cout<<"parent process exit"<<endl;
	return 0;
}
