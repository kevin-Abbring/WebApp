#include "signal.h" 
#include "unistd.h" 

#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>

using namespace std;

int main(int argc,char**argv) 
{ 
	if(argc!=4)
	{
		cout<<"Should input: ";
		cout<<"Function Name(string), Signum(int), Object pid(int)";
		cout<<endl;
		exit(0);	
	}

	pid_t pid; 
	string sFUNC=argv[1];
	int signum=atoi(argv[2]); //signum or delay time
	pid=atoi(argv[3]);

	cout<<"current pid is "<<getpid()<<endl;
	if(pid<=0)
	{
		for(int i=0;i<5;i++)
		{
			if(fork()==0)
			{
				for(;;)
				{				
					cout<<"child process "<<getpid()<<endl;
					sleep(1);
				}
			}	
		}
	
	}	

	sleep(10);
	if(sFUNC=="kill")
	{
		kill(pid,signum);
		sleep(5);
	}else if(sFUNC=="raise"){
		raise(signum);
		sleep(5);
	}else if(sFUNC=="alarm"){
		alarm(signum);		
		sleep(5);
	}else if(sFUNC=="abort"){
		abort();		
		sleep(5);
	}

	int m=0;
	if(pid==0)
		sleep(100);
	else
		sleep(10);

	kill(0,SIGINT);
	cout<<"kill 0 is sent"<<endl;
	for(;;)
	{
		pid_t p=wait(NULL);	
		if(p==-1)
			break;
		else
		{
			m++;
			cout<<m<<" child process closed,pid is: "<<p<<endl;
		}
	}
	cout<<"Finished!"<<endl;
	sleep(5); 
} 
