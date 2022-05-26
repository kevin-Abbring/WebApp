#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// windows��winsock.h/winsock2.h 
// linux��sys/socket.h
// ��ͬƽ̨ͷ�ļ���һ��
// #include <winsock.h> ���� #include <winsock2.h>
// <arpa/inet.h>��<windows.h>����

#define MAXDATASIZE 128
#define PORT 3000
#define BACKLOG 5

int main(int argc,char **argv){
	int sockfd,new_fd,nbytes,sin_size;
	char buf[MAXDATASIZE];
	struct sockaddr_in srvaddr,clientaddr;
	
	//1.��������˵�
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("can;t create socket\n");
		exit(1);
	}
	//����ַ
	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;/* IP protocol family.   IP version 6.  */
	srvaddr.sin_port=htons(PORT);
	if(inet_aton("127.0.0.1",srvaddr.sin_addr.s_addr)==-1){
		printf("addr convert error\n");
		exit(1);
	}
	//2.�󶨷�������ַ�Ͷ˿�
	if(
		bind(//�����ص�ַ��socket������
			sockfd, 
			(struct sockaddr *)&srvaddr,
			sizeof(struct sockaddr)
			)==-1
	)
	{
		printf("bindt error\n");
		exit(1);
	}
//3. �����˿�
//TCPЭ��Ϊÿ������socketά���������У�
//δ������Ӷ��к���������Ӷ���
	if(
		listen(
			sockfd, //�󶨺õ�socket������
			BACKLOG //ָ����������Ӷ��е���󳤶� 
			)==-1
	)
	//ִ��listen������socketת���ɱ���socket�����Խ������ӣ�
	{
		printf("listen error\n");
		exit(1);
	}
	for(;;){
		//4.���ܿͻ�������
		sin_size=sizeof(struct sockaddr_in);
		if((new_fd=
			accept(
/*	accept�������ص�socket���������������ԺͿͻ���ͨ�ŵ�socket��
	������������socketֻ�������ӣ���������ͨ��
	accept������û������ɵ�����ʱ����������                   */
				sockfd,
				(struct sockaddr *)&clientaddr,//clinet��ַ
				&sin_size //��ַ�ṹ����
				))==-1)
		{
			printf("accept errot\n");
			continue;
		}
		//5.��������
/*
ϵͳ���ջ������е����ݴ��ڲ���lenʱ����len
�������е�����С�ڲ���lenʱ����ʵ�ʳ��� 
���ջ�������û������ʱread���������������������ʱ����
�յ����� 
���ӱ��رգ�����0 
���ӱ���λ�����ش��� 
�����������յ��ж��źţ�errno=EINTR 
��ȡ�������ݵ�read_all����
*/
		nbytes=read(
				new_fd, //���յ���socket������
				buf,  //�������ݻ���
				MAXDATASIZE  //��ȡ���ݴ�С
				);
		buf[nbytes]='\0';
		printf("client:%s\n",buf);
		printf("client:%d\n",nbytes);
		
		//6.������Ӧ
		sprintf(buf,"wellcome!");//дbuff
		write(
			new_fd,
			buf,
			strlen(buf)
			);
		//�ر�socket
		/*
		����closeֻ�ǽ���sockfd�����ü�1��
		ֱ����sockfd������Ϊ0ʱ�����sockfd ��
		TCPЭ�齫����ʹ��sockfd��ֱ���������ݷ������ 
		*/
		close(new_fd);
	}
	close(sockfd);
}
