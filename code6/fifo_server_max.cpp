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

int main(int argc,char **argv)
{
	int last=-1;	
	string str="/tmp/fifo_test";
	string str1=str+"0";
	int k=mkfifo(str1.c_str(),O_CREAT|O_EXCL);
	if(k<0 && (errno!=EEXIST))
	{
		cout<<"create 1st fifo error."<<endl;
		exit(1);
	}
	cout<<"fifo0: k="<<k<<endl;
	
	int n=atoi(argv[1]);
	for(int i=1;i<n;i++)
	{
		str1=str+to_string(i);
		int m=mkfifo(str1.c_str(),O_CREAT|O_EXCL);
		if(m<0 && (errno!=EEXIST))
		{
			cout<<"Failed to create the "<<i<<" fifo."<<endl;
			cout<<"last="<<last<<endl;
			exit(1);
		}		
		else
			last=m;
	}
	cout<<"Finished."<<endl;
	cout<<"Created "<<n<<" fifos."<<endl;
	cout<<"last="<<last<<endl;
	sleep(60);
	return 0;
}

