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
	int n=atoi(argv[1]);	//最大进程数目
	int m=atoi(argv[2]);	//分组显示大小
	int d=atoi(argv[3]);	//父进程延时秒数
	
	cout<<"Current pid is "<<getpid()<<endl;

	for(int i=0;i<n;i++)
	{	
		pid=fork();
		if(pid==0)	//子进程程序
		{
			for(;;)
			{
				sleep(1);
			}
		}
		else if(pid<0)	//调用失败
		{
			cout<<"Failed to create the "<<i<<" child process."<<endl;
			break;
		}
		
		if(i%m==0)
			cout<<"the "<<i/m<<"*"<<m<<" processes is created, the last pid is "<<pid<<endl;
	}
	cout<<"Finished."<<endl;
	sleep(d);

	kill(0,SIGINT);
	sleep(10);
	cout<<"parent process exit"<<endl;
	return 0;
}
