#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXDATASIZE 128
#define PORT 3000

void show_addr(struct hostent *he);
int addr_conv(char *address,struct in_addr *inaddr);

int main(int argc,char **argv){
	int sockfd,nbytes;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr;
	if(argc<2){
		printf("usage:./client hostname|ip\n");
		exit(0);
	}
	//1.创建网络端点
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("can;t create socket\n");
		exit(1);
	}
	//指定服务器地址（本地socket地址采用默认值）
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(PORT);
	if(addr_conv(argv[1],&srvaddr.sin_addr)==-1){
			perror(strerror(errno));
	}

	//2.连接服务器
	if(connect(sockfd,(struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1){
		printf("connect error\n");
		exit(1);
	}
	//3.发送请求
	sprintf(buf,"hello");
	write(sockfd,buf,strlen(buf));
	//4.接收响应
	if((nbytes=read(sockfd,buf,MAXDATASIZE))==-1){
		printf("read error\n");
		exit(1);
	}
	buf[nbytes]='\0';
	printf("srv respons:%s\n",buf);
	//关闭socket
	close(sockfd);
	return 0;
}

int addr_conv(char *address,struct in_addr *inaddr){
	struct hostent *he;
	if(inet_aton(address,inaddr)!=0){
		printf("call inet_aton sucess.\n");
		return 0;
	}
	printf("call inet_aton fail.\n");
	he=gethostbyname(address);
	if(he!=NULL){
		printf("call gethostbyname sucess.\n");
		show_addr(he);
		*inaddr=*((struct in_addr *)(he->h_addr_list[0]));
		return 0;
	}
	return -1;
}

void show_addr(struct hostent *he)
{
	int i;
	
	printf("h_name:%s\n",he->h_name);
	printf("h_length:%d\n",he->h_length);
	printf("h_addrtype:%d\n",he->h_addrtype);
	for(i=0;he->h_aliases[i] !=NULL;i++)
		printf("h_aliases%d:%s\n",i+1,he->h_aliases[i]); 
	//列出所有地址
	for(i=0;he->h_addr_list[i]!=NULL;i++){
		struct in_addr *addr;
		addr=(struct in_addr *)he->h_addr_list[i];
		printf("ip%d:%s\n",(i+1),inet_ntoa(*addr));
	}
}
