#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <iostream>

#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 

using namespace std;

int main(int argc,char **argv)
{
	int pipe1[2],pipe2[2];
	int pipe3[2],pipe4[2];

	char psend1[]="hello";
	char psend2[]="welcome";
	char precv1[16];
	char precv2[16];
	pid_t pid;

	if(pipe(pipe1)<0 || pipe(pipe2) || pipe(pipe3)<0 || pipe(pipe4)<0)
		cout<<"pipe error"<<endl;
	
	pid=fork();
	if(pid<0)
		exit(1);
	else if(pid==0){	//child B,use pipe1&2	
		cout<<"child B..."<<endl;
		close(pipe1[1]);//关闭pipe1写端口
		close(pipe2[0]);//关闭pipe2读端口
		close(pipe3[0]);close(pipe3[1]);//关闭pipe3
		close(pipe4[0]);close(pipe4[1]);//关闭pipe4

		if(read(pipe1[0],precv1,16)>0)
			cout<<"child B received:"<<precv1<<endl;
		write(pipe2[1],psend2,sizeof(psend2));
		exit(0);
	}

	pid=fork();
	if(pid<0)
		exit(1);
	else if(pid==0){	//child A,use pipe3&4	
		cout<<"child A..."<<endl;
		close(pipe3[1]);//关闭pipe3写端口
		close(pipe4[0]);//关闭pipe4读端口
		close(pipe1[0]);close(pipe1[1]);//关闭pipe1
		close(pipe2[0]);close(pipe2[1]);//关闭pipe2

		write(pipe4[1],psend1,sizeof(psend2));
		if(read(pipe3[0],precv2,16)>0)
			cout<<"child A received:"<<precv2<<endl;
		exit(0);
	}

	//父进程,用管道1&3写数据,管道2&4读数据
	close(pipe1[0]);//关闭pipe1读端口
	close(pipe2[1]);//关闭pipe2写端口

	close(pipe3[0]);//关闭pipe3读端口
	close(pipe4[1]);//关闭pipe4写端口

	read(pipe4[0],precv1,16);
	write(pipe1[1],precv1,sizeof(precv1));
	read(pipe2[0],precv2,16);
	write(pipe3[1],precv2,sizeof(precv2));
	
	cout<<"finish."<<endl;
}	


