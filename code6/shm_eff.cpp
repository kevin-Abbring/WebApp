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

#include <sys/ipc.h>
#include <sys/shm.h>

#define  MY_SHM "/dev/null"

using namespace std;

void sigint_handler(int);
int shm_id;

main(int argc, char** argv)
{
	int temp;
	int* p_int;
	key_t key;
		

	if(argc!=3)
	{
		cout<<"usage:./shm_eff -a b, a:-s-- shm, -m--mem"<<endl;
		cout<<"						  b:-any int--w/r times"<<endl;
		exit(1);	
	}

	int mSize=1024*1024;	
	int mem[mSize];
	int times=atoi(argv[2]);
	
	srand((int)time(NULL));
	
	key=ftok(MY_SHM,'b');
	if(key==-1)
	{
		perror("ftok error");
		exit(1);	
	}

	if(strcmp(argv[1],"-s")==0)
	{
		shm_id=shmget(key,mSize*sizeof(int),0777);
		if(shm_id==-1)
		{
			perror("shmget error");
			exit(1);
		}

		p_int=(int*)shmat(shm_id,0,0);
		cout<<"begin to write shm..."<<endl;
		for(int j=0;j<times;j++)
		{		
			for(int i = 0;i<mSize;i++)
			{
				temp=rand();
				memcpy(p_int+i,&temp,sizeof(int));
			}
		}
		cout<<"finished writing shm!"<<endl;
		if(shmdt(p_int)==-1)
		{
			perror(" detach error ");
			exit(1);
		}
	}
	else if(strcmp(argv[1],"-m")==0)
	{
		p_int=mem;
		cout<<"begin to write mem..."<<endl;
		for(int j=0;j<times;j++)
		{		
			for(int i = 0;i<mSize;i++)
			{
				temp=rand();
				memcpy(p_int+i,&temp,sizeof(int));
			}
		}
		cout<<"finished writing mem!"<<endl;
	}
}

void sigint_handler(int sig)
{
	shmctl(shm_id, IPC_RMID, NULL);
	cout<<"share memeory deleted"<<endl;
	exit(0);
}
