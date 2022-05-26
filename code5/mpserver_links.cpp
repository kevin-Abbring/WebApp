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

#define MAXDATASIZE 128
#define PORT 3000
#define BACKLOG 5

int main(int argc,char **argv){
	int sockfd,new_fd,nbytes;
	socklen_t sin_size;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr,clientaddr;
	
/*	struct sigaction act,oldact;
	
	act.sa_handler=SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	if(sigaction(SIGCHLD,&act,&oldact)<0){
		printf("sigaction error.");
		exit(1);
	}

*/	//1.创建网络端点
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("can;t create socket\n");
		exit(1);
	}
	
	if(argc==2){
		int on=1;
		setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		printf("reuse addr\n");
	}
	//填充地址
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(PORT);
	srvaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	//2.绑定服务器地址和端口
	if(bind(sockfd,(struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1){
		printf("bind error\n");
		exit(1);
	}
	//3. 监听端口
	if(listen(sockfd,BACKLOG)==-1){
		printf("listen error\n");
		exit(1);
	}
	cout<<"The server pid is "<<getpid()<<endl;
		
	for(;;){
		//4.接受客户端连接
		sin_size=sizeof(struct sockaddr_in);
		if((new_fd=accept(sockfd,(struct sockaddr *)&clientaddr,&sin_size))==-1){
			printf("accept error\n");
			continue;
		}
		pid_t pid=fork();
		if(pid==0){
			//子进程完成客户端处理
			printf("client addr:%s %d\n",
			inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
			//5.接收请求
			nbytes=read(new_fd,buf,MAXDATASIZE);
			buf[nbytes]='\0';
			printf("client:%s\n",buf);
		
			//6.回送响应
			sprintf(buf,"wellcome!");
			write(new_fd,buf,strlen(buf));
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
			printf("create child process error.\n");		
		}
	}
	close(sockfd);
	
	return 0;
}
