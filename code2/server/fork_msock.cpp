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
	int i,m;	
	int n=atoi(argv[1]);
		
	for(i=0;i<n;i++)
	{	
		pid=fork();
		if(pid==0)	//子进程程序
		{
			cout<<"child process: pid="<<getpid()<<endl;
			m=i*1005+2000;
			string str=to_string(m);
			execlp("./server_msock","./server_msock",str.c_str(),"1000",NULL);
			exit(0);
		}
		else if(pid>0)	//父进程程序
		{
			cout<<"parent process: pid="<<getpid()<<endl;
			sleep(1);
		}
		else	//调用失败
			cout<<"create child process fail"<<endl;
	}
	
	sleep(60);
	for(int i=0;i<n;i++)
		wait(NULL);	

	cout<<"parent process exit"<<endl;
	return 0;
}
