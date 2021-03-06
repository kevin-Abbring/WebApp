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

using namespace std;

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <signal.h>

#define  SEM_NAME "/tmp/sem_name.tmp"
#define  SEM_NUM 12

void sigint_handler(int);
int semid;
struct sembuf semf;

int main(int argc,char*argv[])
{
	int i,n,m,bOnce;
	key_t key;
	short initarray[SEM_NUM],outarray[SEM_NUM],old_outarray[SEM_NUM];
  
	for(i=0;i<SEM_NUM;i++)
	{
		initarray[i]=5;
		outarray[i]=0;
		old_outarray[i]=0;

	}
	
	key=ftok(SEM_NAME,'a');
	if(argc!=3)
	{
		cout<<"usage:./semp -x y, :-c n--create n, -n +m--inc,-n -m--dec"<<endl;
		exit(1);	
	}
	
	if(strcmp(argv[1],"-c")==0)
	{
		signal(SIGINT,sigint_handler);
		semid=semget(key,SEM_NUM,0777|IPC_CREAT);
		semctl(semid,SEM_NUM,SETALL,initarray);
		cout<<semid<<endl;	
		for(;;)
		{
			semctl(semid,SEM_NUM,GETALL,outarray);
			for(i=0;i<SEM_NUM;i++)
			{
				if(outarray[i]!=old_outarray[i])
				{
					old_outarray[i]=outarray[i];
					bOnce=1;
				}	
			}	
					
			if(bOnce)
			{
				cout<<"semaps current vals: ";
				for(i=0;i<SEM_NUM;i++)			
					cout<<outarray[i]<<"\t";
				cout<<endl;
				bOnce=0;			
			}
			sleep(1);
		}
	}else{
		n=atoi(argv[1]);		
		if(n<1 || n>SEM_NUM)
		{
			cout<<"The number of semaphore should be between 1 and "<<SEM_NUM<<endl;
			exit(0);
		}

		m=atoi(argv[2]);
		
		semid=semget(key,SEM_NUM,0777);
		semf.sem_num=n;
		semf.sem_op=m;
		semf.sem_flg=SEM_UNDO;
		cout<<semid<<endl;
	
		if(semop(semid,&semf,1)==-1) //1—操作个数
			cout<<"process: "<<getpid()<<" op semaphore "<<n<<" failed"<<endl;
		else
			cout<<"process: "<<getpid()<<" op semaphore "<<n<<" successed"<<endl;
	
		sleep(15);
	}
}
	
	
void sigint_handler(int sig)
{
	semctl(semid,SEM_NUM,IPC_RMID,0);
	cout<<"semaphore deleted"<<endl;
	exit(0);
}
