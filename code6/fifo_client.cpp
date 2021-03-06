#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <errno.h>
#include<stdio.h> 
#include<stdlib.h> 

#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

using namespace std;

#define FIFO_NAME	"/tmp/fifo_test"

int main(int argc,char **argv)
{
	char buf[1024];	
	int fd;
	if(argc==2&&strcmp(argv[1],"-b")==0)
		fd=open(FIFO_NAME,O_RDONLY,0);
	else
		fd=open(FIFO_NAME,O_RDONLY|O_NONBLOCK,0);
	if(fd!=-1)
		cout<<"open success"<<endl;
	else{
		perror("open fail");
		return 0;
	}
	int read_num=20;
	memset(buf,0,sizeof(buf));
	read_num=read(fd,buf,1024);
	if(read_num==-1)
	{
		if(errno==EAGAIN)
			cout<<"no data,try later:"<<endl;
	}
	else
	{
		cout<<"real read bytes:"<<read_num<<endl;
		cout<<"read data:"<<buf<<endl;
	}	
	//删除管道文件
	//unlink(FIFO_NAME);
	return 0;
}

