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

#include <sched.h>
#include <pthread.h>

using namespace std;

void* thread(void *arg)  
{  
   *(int*)arg = 0; 
	for(;;)
	{
	//	sleep(1);
	}	 
   return arg;  
} 

int main(int argc,char **argv)
{
	pid_t pid;
	pthread_t th;
	int last=-1;
   int ret;  
   int arg = 10;  
   int *thread_ret = NULL;  
    
	int n=atoi(argv[1]);	//最大进程数目
	int m=atoi(argv[2]);	//分组显示大小
	int d=atoi(argv[3]);	//父进程延时秒数
	
	cout<<"The base pid is "<<getpid()<<endl;
	
	for(int i=0;i<n;i++)
	{
		ret = pthread_create(&th, NULL, thread, &arg);  
	   if(ret !=0)
		{  
      	cout<<"Failed to create "<<i<<" thread!"<<endl;  
	      cout<<"The last thread id is "<<last<<endl;
			exit(1);  
	   }
				
		last=th;
		if(i%m==0)
		{				
			cout<<"the "<<i/m<<"*"<<m<<" thread is created, id "<<th<<endl;
		}
		
	}
	cout<<"Finished."<<endl;
	sleep(d);

	kill(0,SIGINT);
	sleep(10);
	cout<<"parent process exit"<<endl;
	return 0;
}
