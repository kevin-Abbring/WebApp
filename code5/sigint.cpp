#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void sigint_handler(int);
int main(int argc,char **argv)
{
	char buf[10];
	int n=0;
	
	if(argc==2&&strcmp(argv[1],"-s")==0)
	{
		struct sigaction act;
		act.sa_handler=sigint_handler;
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;//SA_RESETHAND;//SA_ONESHOT;
		sigaction(SIGINT,&act,NULL);
	}
	cout<<"pid= "<<getpid()<<endl;
	n=read(0,buf,sizeof(buf));
	
	if(n<0){
		if(errno==EINTR)
			cout<<"read interrupted."<<endl;
		else
			cout<<"read error:"<<strerror(errno)<<endl;
	}
	if(n>0)
		write(1,buf,n);
	for(;;){}
	//sleep(10);//exit when recv sigint
}

void sigint_handler(int sig)
{
	cout<<endl;
	cout<<"signal process function"<<endl;
	cout<<"signal "<<sig<<" is captured."<<endl;
}
