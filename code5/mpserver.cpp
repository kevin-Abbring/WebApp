#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <signal.h>

using namespace std;

#define RECVSIZE 8
#define BACKLOG 5

int main(int argc,char **argv){
	int sockfd,new_fd,nbytes;
	short port;
	socklen_t sin_size;
	char buf[RECVSIZE];
	int *pi;
	char* pc;
	char* pc0;
	int m,n,i;
	struct sockaddr_in srvaddr,clientaddr;

	if(argc!=4){
		cout<<"Please input: port -x -y. (x--c clear zombie, other not; y--r ReUseAddr, other not)"<<endl;
		exit(0);	
	}

	port=atoi(argv[1]);	

	//1.创建网络端点
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("can;t create socket\n");
		exit(1);
	}

	if(strcmp(argv[2],"-c")==0)
	{
		cout<<"clear zombie"<<endl;
		struct sigaction act,oldact;
	
		act.sa_handler=SIG_IGN;
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;
		if(sigaction(SIGCHLD,&act,&oldact)<0)
		{
			cout<<"sigaction error.";
			exit(1);
		}
	}

	if(strcmp(argv[3],"-r")==0)
	{
		int on=1;
		setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		cout<<"reuse addr"<<endl;
	}

	//填充地址
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(port);
	srvaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	//2.绑定服务器地址和端口
	if(bind(sockfd,(struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1){
		cout<<"bind error"<<endl;
		exit(1);
	}
	//3. 监听端口
	if(listen(sockfd,BACKLOG)==-1){
		cout<<"listen error"<<endl;
		exit(1);
	}
	cout<<"The server pid is "<<getpid()<<endl;
		
	for(;;){
		//4.接受客户端连接
		sin_size=sizeof(struct sockaddr_in);
		if((new_fd=accept(sockfd,(struct sockaddr *)&clientaddr,&sin_size))==-1){
			cout<<"accept error"<<endl;
			continue;
		}
		pid_t pid=fork();
		if(pid==0){
			//子进程完成客户端处理
			cout<<"client addr:"<<inet_ntoa(clientaddr.sin_addr)
				<<", "<<ntohs(clientaddr.sin_port)<<endl;
			//5.接收请求
			nbytes=read(new_fd,buf,RECVSIZE);
			pc=(char*)&m;
			pc0=buf;
			for(i=0;i<sizeof(int);i++)
			{
				*pc=*pc0;
				pc++;
				pc0++;
			}
			
			pc=(char*)&n;
			for(i=0;i<sizeof(int);i++)
			{
				*pc=*pc0;
				pc++;
				pc0++;
			}
	
			m=ntohl(m);
			n=ntohl(n);
			cout<<"client:"<<m<<",  "<<n<<endl;
		
			//6.回送响应
			m += n;
			cout<<"result:"<<m<<endl;
			m=htonl(m);
			write(new_fd,(char*)&m,sizeof(int));
			//关闭socket
			close(new_fd);
			
			cout<<"The child pid is "<<getpid()<<endl;
			sleep(60);
			exit(0);
		}
		else if(pid>0){
			//父进程继续接受其他客户端连接
			close(new_fd);
		}
		else{
			cout<<"create child process error."<<endl;		
		}
	}
	close(sockfd);
	
	return 0;
}
