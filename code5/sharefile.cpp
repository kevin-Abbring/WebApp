#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 
//--open root dir: sudo nautilus
//--sudo su
//--set root psw: sudo passwd root
//--root: su root
 

using namespace std;

int		var=0;

int main(int argc,char **argv){
	int 	fd;
	pid_t 	pid;
	char	pbuf[2];
	
	fd=open("/root/test.txt",O_RDONLY);
	read(fd,pbuf,1);
	cout<<"before fork pbuf[0]="<<(short)pbuf[0]<<",var="<<var<<endl;
	cout<<"parents fd="<<fd<<endl;
	pid=fork();
	if(pid==0){
		//子进程程序
		char cbuf[2];
		lseek(fd,15,SEEK_CUR);//读取当前文件指针位置
		read(fd,cbuf,1);
		var=10;
		cout<<"cbuf[0]="<<(short)cbuf[0]<<",var="<<var<<endl;
		cout<<"child fd="<<fd<<endl;
		
		exit(0);
	}
	else if(pid>0){
		//父进程程序
		wait(NULL);//等待子进程结束
		read(fd,pbuf,1);
		cout<<"after fork pbuf[0]="<<(short)pbuf[0]<<",var="<<var<<endl;
		cout<<"parents fd="<<fd<<endl;
	}
	else{
		//调用失败
		cout<<"create child process fail"<<endl;
	}
	close(fd);
	return 0;
}
