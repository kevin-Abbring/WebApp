#include <iostream>
#include <unistd.h>

#include "server302.h"

void serv_response(int sockfd)
{
  int i,nbytes;
  int buf_recv[1024];
  int buf_send[1024];

  nbytes=read(sockfd,(char*)buf_recv,1024*sizeof(int));
  if(nbytes<=0 || nbytes%sizeof(int)!=0)
	return;
 	
  int nNum= nbytes/sizeof(int);
  int* pn=buf_recv;

  for(i=0;i<nNum;i++)	
  {
	*pn=ntohl(*pn);
	pn++;
  }

  switch(buf_recv[0])	//函数代号，get_the_Avg
  {
    case 2:
	
	if(nNum<2 || nNum-2!=buf_recv[1])
	{
		std::cout <<"Data error"<<std::endl;
	  	break;
	}

	nNum=get_the_Avg(nNum-2,&buf_recv[2]);
	buf_send[0]=nNum;
	buf_send[0]=htonl(buf_send[0]);
		
	//nbytes=write_all(sockfd,（char*）buf_send,nNum*sizeof(int));
	nbytes=write(sockfd,(char*)buf_send,sizeof(int));
	if(nbytes<=0)
		std::cout <<"Write error"<<std::endl;
	  
	break;
	
    default:	//函数代号，其它
	std::cout <<"No this function"<<std::endl;
	break;  
  }
}

int get_the_Avg(int nNum,int* pnData)
{
  int i,nAvg,nAvg1;
  int* pn;

  pn=pnData;
  nAvg=0;
  nAvg1=0;	
  for(i=0;i<nNum;i++)
  {
	nAvg1+=*pn;
	pn++;
  }
  
  if(nNum>0)
  {
	nAvg1=nAvg1*2/nNum;
  	nAvg=nAvg1/2;
	nAvg1=nAvg1%2;
	if(nAvg1>0)
		nAvg++;
  }
  
  return nAvg;
}


