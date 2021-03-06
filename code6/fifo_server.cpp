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
	char pstr[]="server data";
	
	if(mkfifo(FIFO_NAME,O_CREAT|O_EXCL)<0&&(errno!=EEXIST))
		cout<<"create fifo error"<<endl;

	int fd;
	if(argc==2&&strcmp(argv[1],"-b")==0)
		fd=open(FIFO_NAME,O_WRONLY,0);
	else
		fd=open(FIFO_NAME,O_WRONLY|O_NONBLOCK,0);
	if(fd!=-1)
		cout<<"open success"<<endl;
	else{
		perror("open fail");
		return 0;
	}
	int write_num=write(fd,pstr,sizeof(pstr));
	if(write_num==-1){
		if(errno=EAGAIN)
			cout<<"write fifo error,try later:"<<endl;
	}	
	else
		cout<<"real write num is:"<<write_num<<endl;
	return 0;
}

