#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>

#include <iostream>
#include <sys/time.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <iomanip>

#include "comm_func.h"

using namespace std;

void send_icmp(int sockfd,sockaddr_in send_addr);
void recv_icmp(int sockfd,sockaddr_in send_addr);

int main(int argc,char **argv)
{
	int sockfd;
	sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
	if(sockfd<0)
	{
		cout<<"creat socket error"<<endl;
		cout<<strerror(errno)<<endl;

		return 1;
	}
	sockaddr_in send_addr;
	bzero(&send_addr,sizeof(send_addr));
	send_addr.sin_family=AF_INET;
	addr_conv(argv[1],&send_addr.sin_addr);
	for(int i=0;i<3;i++)
	{
		send_icmp(sockfd,send_addr);
		recv_icmp(sockfd,send_addr);
		sleep(3);
	}
	return 0;
}

unsigned short checksum(unsigned short *addr,int len)
{
	int nleft=len;
	int sum=0;
	unsigned short *w=addr;
	unsigned short answer=0;
	while(nleft>1)
	{
		sum+=*w++;
		nleft-=2;
	}
	if(nleft==1)
	{
		*(unsigned char *)(&answer)=*(unsigned char *)w;
		sum+=answer;
	}
	sum=(sum>>16)+(sum&0xffff);
	sum+=(sum>>16);
	answer=(unsigned short)sum&0xffff;
	return ~answer;
}

void send_icmp(int sockfd,sockaddr_in send_addr)
{
	static short int seq=0;
	char  buf[8+8];
	struct icmphdr *icmp=(struct icmphdr *)buf;
	//填充icmp首部
	icmp->type=ICMP_ECHO;
	icmp->code=0;
	icmp->checksum=0;
	icmp->un.echo.id=getpid();
	icmp->un.echo.sequence=seq++;
	//填充icmp数据(时间)
	struct timeval tv;
	gettimeofday(&tv,NULL);
	memcpy(buf+8,&tv,sizeof(tv));
	int buflen=sizeof(struct icmphdr)+sizeof(struct timeval);
	//计算校验和
	icmp->checksum=checksum((unsigned short *)buf,buflen);
	//发送icmp数据包
	cout<<"send..."<<endl;
	int len=sendto(sockfd,buf,buflen,0,(struct sockaddr *)&send_addr,sizeof(send_addr));
	if(len<0)
		cout<<"send icmp error"<<endl;
}

void recv_icmp(int sockfd,sockaddr_in send_addr)
{
	char buf[256];
	struct icmphdr *icmp;
	struct ip *ip;
	int ipheadlen;
	int icmplen;
	//接收icmp响应
	for(;;)
	{
		cout<<"recv..."<<endl;
		int n=recvfrom(sockfd,buf,sizeof(buf),0,NULL,NULL);
		if(n<0)
		{
			cout<<"recv error"<<endl;
			continue;
		}
		
		//显示ip数据包
		cout<<"received "<<n<<"bytes"<<endl;
		int i=0,j=0;
		int m=n/4;
		int k=n%4;
		for(int h=0;h<m;h++)
		{
			for(j=0;j<4;j++)
			{
				cout<<std::hex<<((short)buf[i] & 0xff)<<"\t";
				i++;
			}
			cout<<""<<endl;
		}
		
		for(j=0;j<k;j++)
		{
			cout<<std::hex<<((short)buf[i] & 0xff)<<"\t";
			i++;
		}
		cout<<"finish"<<endl;

		ip=(struct ip *)buf;	
		ipheadlen=ip->ip_hl<<2;
		icmplen=n-ipheadlen;
		cout<<"icmplen..."<<icmplen<<endl;
		if(icmplen<16)
			continue;
		icmp=(struct icmphdr *)(buf+ipheadlen);
		if(icmp->type==ICMP_ECHOREPLY && icmp->un.echo.id==getpid())
			break;
	}
	//计算时间差
	struct timeval recv_tv;
	gettimeofday(&recv_tv,NULL);
	struct timeval send_tv;
	memcpy(&send_tv,icmp+1,sizeof(send_tv));
	recv_tv.tv_sec-=send_tv.tv_sec;
	recv_tv.tv_usec+=recv_tv.tv_sec*1000000L;
	long interval=recv_tv.tv_usec-send_tv.tv_usec;
	//输出信息
	cout<<icmplen<< " bytes from "<<inet_ntoa(send_addr.sin_addr);
	cout<<" icmp_seq="<<icmp->un.echo.sequence<<" bytes="<<icmplen<<" ttl="<<(int)ip->ip_ttl;
	cout<<" time="<<(float)interval/1000.0<<"ms"<<endl;
}
