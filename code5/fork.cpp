#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 

using namespace std;

int main(int argc,char **argv)
{
	pid_t child_pid=fork();
	if(child_pid==0){
		//子进程程序
		for(int i=0;i<5;i++){
			cout<<"child process:ppid="<<getppid()<<",pid="<<getpid()<<endl;
			sleep(1);
		}
		exit(0);
	}
	else if(child_pid>0){
		//父进程程序
		for(int i=0;i<5;i++){
			cout<<"parent process:ppid="<<getppid()<<",pid="<<getpid()<<endl;
			sleep(2);
		}
		wait();
	}
	else{
		//调用失败
		cout<<"create child process fail"<<endl;
	}
	return 0;
}
