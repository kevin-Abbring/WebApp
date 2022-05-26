#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// windows下winsock.h/winsock2.h 
// linux下sys/socket.h
// 不同平台头文件不一样
// #include <winsock.h> 或者 #include <winsock2.h>
// <arpa/inet.h>用<windows.h>代替

#define MAXDATASIZE 128
#define PORT 3000
#define BACKLOG 5

int main(int argc,char **argv){
	int sockfd,new_fd,nbytes,sin_size;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr,clientaddr;
	
	//1.创建网络端点
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("can;t create socket\n");
		exit(1);
	}
	//填充地址
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;/* IP protocol family.   IP version 6.  */
	srvaddr.sin_port=htons(PORT);
	if(inet_aton("127.0.0.1",srvaddr.sin_addr.s_addr)==-1){
		printf("addr convert error\n");
		exit(1);
	}
	//2.绑定服务器地址和端口
	if(
		bind(//将本地地址给socket描述符
			sockfd, 
			(struct sockaddr *)&srvaddr,
			sizeof(struct sockaddr)
			)==-1
	)
	{
		printf("bindt error\n");
		exit(1);
	}
//3. 监听端口
//TCP协议为每个侦听socket维护两个队列：
//未完成连接队列和已完成连接队列
	if(
		listen(
			sockfd, //绑定好的socket描述符
			BACKLOG //指定已完成连接队列的最大长度 
			)==-1
	)
	//执行listen函数后socket转换成被动socket，可以接受连接，
	{
		printf("listen error\n");
		exit(1);
	}
	for(;;){
		//4.接受客户端连接
		sin_size=sizeof(struct sockaddr_in);
		if((new_fd=
			accept(
/*	accept函数返回的socket描述符是真正可以和客户端通信的socket，
	服务器的侦听socket只接受连接，不能用于通信
	accept函数在没有已完成的连接时将阻塞进程                   */
				sockfd,
				(struct sockaddr *)&clientaddr,//clinet地址
				&sin_size //地址结构长度
				))==-1)
		{
			printf("accept errot\n");
			continue;
		}
		//5.接收请求
/*
系统接收缓冲区中的数据大于参数len时返回len
缓冲区中的数据小于参数len时返回实际长度 
接收缓冲区中没有数据时read函数阻塞，出现下列情况时返回
收到数据 
连接被关闭，返回0 
连接被复位，返回错误 
阻塞过程中收到中断信号，errno=EINTR 
读取完整数据的read_all函数
*/
		nbytes=read(
				new_fd, //接收到的socket描述符
				buf,  //接收数据缓冲
				MAXDATASIZE  //读取数据大小
				);
		buf[nbytes]='\0';
		printf("client:%s\n",buf);
		printf("client:%d\n",nbytes);
		
		//6.回送响应
		sprintf(buf,"wellcome!");//写buff
		write(
			new_fd,
			buf,
			strlen(buf)
			);
		//关闭socket
		/*
		调用close只是将对sockfd的引用减1，
		直到对sockfd的引用为0时才清除sockfd ，
		TCP协议将继续使用sockfd，直到所有数据发送完成 
		*/
		close(new_fd);
	}
	close(sockfd);
}
