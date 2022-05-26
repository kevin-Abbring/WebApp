#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define  SERVER_PORT 8086

int selectbigger(int* buf,int len_in,int* pn_out,int* piLen_out)
{
  int sockfd;
  struct sockaddr_in servaddr;
  int buf_recv[2048];
  int *pn;

  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
  {
	fprintf(stderr,"Socket error\n");
	return 0;
  }
  
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(SERVER_PORT);
  //if(inet_aton(“192.168.0.1”,&servaddr.sin_addr)==-1)
  if(inet_aton("127.0.0.1",&servaddr.sin_addr)==-1)
  {
	fprintf(stderr,"Inet_aton error\n");
	return 0;
  }

  if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
	fprintf(stderr,"Connect error\n");
	close(sockfd);
	return 0;
  }
 

  int* pbuf=buf;
  int i,n;

  for(i=0;i<len_in;i++)					//字节顺序
  {
	n=htons(*pbuf);
	*pbuf=n;
	pbuf++;
  }
  
  char* pc=(char*)buf;
  int nbytes=write(sockfd,pc,256*sizeof(int));
  if(nbytes<=0)
  {
	fprintf(stderr,"Write error\n");
	close(sockfd);	  
	return 0;
  }



  pc=(char*)buf_recv;
  nbytes=read(sockfd,pc,256*sizeof(int));
  if(nbytes<=0)
  {
	fprintf(stderr,"Read error\n");
	close(sockfd);	  
	return 0;
  }

  *piLen_out = nbytes/sizeof(int);
  
  sleep(2);
//  *ppn_out = new int[*piLen_out]; 
//  *ppn_out =(int*)malloc((*piLen_out)*sizeof(int));


  pn=buf_recv;  
  for(i=0;i<*piLen_out;i++)					//字节顺序
  {
	n=ntohs(*pn);
//n=*pn;
	*pn=n;
	pn++;
  }
  
  pn=pn_out;  
  for(i=0;i<*piLen_out;i++)					//字节顺序
  {
	*pn=buf_recv[i];
	pn++;
  }

  close(sockfd);
  return 1;
}

int main()
{
  int buf[1024];
  int buf_recv[1024];
  int i;
  int* pn;
  int len;

  printf("The random number is: \n");
  srand((int)time(NULL));
  for(i=0;i<256;i++)
  {
	buf[i]=rand()%200;
	printf("%d ",buf[i]);
  }
  printf("\n\n\n");
  
  if(!selectbigger(buf,256,buf_recv,&len))
	exit(1);

  printf("The number is:%d \n",len-2);

  pn=buf_recv;
  for(i=0;i<len-2;i++)
  {
	pn++;
	printf("%d ",*pn);
  }
  printf("\n");
  
  pn++;
  printf("The average is:%d \n", *pn);

}
