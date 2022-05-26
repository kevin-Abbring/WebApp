#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <iostream>

#include<stdio.h> 
#include<stdlib.h> 


using namespace std;

int main(int argc,char **argv){
	if(fork()==0){
		execlp(argv[1],NULL);
		//返回表示执行错误,打印错误信息
		perror(argv[1]);
		exit( errno );
	}
	else{
		wait(NULL);
	}
	return 0;
}
