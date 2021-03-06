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
#define	MEM_SIZE 256
#define  MY_SHM "/dev/null"

using namespace std;

void sigint_handler(int);
int shm_id;

main(int argc, char** argv)
{
	int i,temp,bOnce;
	int* p_int;
	key_t key;
	int mSize=MEM_SIZE;
	
	if(argc!=2)
	{
		cout<<"usage 2 params:./shm -x, x:-c--create, -m--1M int, -any int--write;"<<endl;
		exit(1);	
	}
	
	if(strcmp(argv[1],"-m")==0)
		mSize=1024*1024;	
	
	int mem[mSize];
	key=ftok(MY_SHM,'b');
	if(key==-1)
	{
		perror("ftok error");
		exit(1);	
	}

	if(strcmp(argv[1],"-c")==0 || strcmp(argv[1],"-m")==0)
	{
		signal(SIGINT,sigint_handler);
		shm_id=shmget(key,mSize*sizeof(int),0777|IPC_CREAT);	
		if(shm_id==-1)
		{
			perror("shmget error");
			exit(1);
		}

		p_int=(int*)shmat(shm_id,0,0);
		for(i = 0;i<MEM_SIZE;i++)
		{
			temp=rand();
			memcpy(p_int+i,&temp,sizeof(int));
		}
		
		if(shmdt(p_int)==-1)
		{
			perror(" detach error ");
			exit(1);
		}
		
		cout<<"shm size is "<<mSize<<endl;		
		
		for(;;)
		{
			p_int=(int*)shmat(shm_id,0,0);
			
			for(i=0;i<MEM_SIZE;i++)
			{
				if(*(p_int+i)!=mem[i])
				{
					mem[i]=*(p_int+i);
					bOnce=1;
				}	
			}	

			if(shmdt(p_int)==-1)
			{
				perror(" detach error ");
				exit(1);
			}		
			
			if(bOnce)
			{
				cout<<"shm current vals: ";
				for(i=0;i<MEM_SIZE;i++)			
					cout<<mem[i]<<"\t";
				cout<<endl;
				bOnce=0;			
			}
			sleep(1);
		}
	}else{
		temp=atoi(argv[1]);
		shm_id=shmget(key,MEM_SIZE*sizeof(int),0777);	
		if(shm_id==-1)
		{
			perror("shmget error");
			exit(1);
		}

		p_int=(int*)shmat(shm_id,0,0);
		for(i = 0;i<MEM_SIZE;i++)
			memcpy(p_int+i,&temp,sizeof(int));
				
		if(shmdt(p_int)==-1)
		{
			perror(" detach error ");
			exit(1);
		}

	}

}

void sigint_handler(int sig)
{
	shmctl(shm_id, IPC_RMID, NULL);
	cout<<"share memeory deleted"<<endl;
	exit(0);
}
