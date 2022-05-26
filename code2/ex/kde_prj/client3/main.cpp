#include <iostream>
#include <unistd.h>

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

//#define  SERVER_ADDR1 "192.168.0.1"
//#define  SERVER_ADDR2 "192.168.0.2"
#define  SERVER_ADDR1 "127.0.0.1"
#define  SERVER_ADDR2 "127.0.0.1"
#define  SERVER_PORT1 8081
#define  SERVER_PORT2 8082

//发送：1，nBegin, nEnd；返回：个数，数据1、数据2、...
//获得nBegin, nEnd之间的所有质数，质数的个数作为返回值
//若函数出错，则返回负值。
int get_the_Data(int nBegin,int nEnd,int* pnData)
{
  int i,sockfd;
  struct sockaddr_in servaddr;

  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
    return 0;
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(SERVER_PORT1);
  if(inet_aton(SERVER_ADDR1,&servaddr.sin_addr)==-1)
  	 return 0;
	
  if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  { 
	close(sockfd);
	return 0;
  }

  int nBuf[3];
  nBuf[0]=htonl(1);	//函数代码,服务器可扩展成为一组功能
  nBuf[1]=htonl(nBegin);
  nBuf[2]=htonl(nEnd);
	
  //int nbytes=write_all(sockfd,(char*)nBuf,3*sizeof(int));
  int nbytes=write(sockfd,(char*)nBuf,3*sizeof(int));
  if(nbytes<=0)
  {
	  std::cout <<"Write error"<<std::endl;
	  close(sockfd); 
	  return -1;
  }
  
  int pnBuf[1024];
  //nbytes=read_all(sockfd,(char*)pnBuf,1024*sizeof(int));
  nbytes=read(sockfd,(char*)pnBuf,1024*sizeof(int));
  if(nbytes<=0 || nbytes%sizeof(int)!=0)
  {
	  std::cout <<"Read error"<<std::endl;
	  close(sockfd);
	  return -1;
  }
  
  int nNum= nbytes/sizeof(int);
  if(nNum<2)
  {
	  std::cout <<"Data error"<<std::endl;
	  close(sockfd); 
	  return -1;
  }
  
  int* pData=pnData;
  for(i=0;i<nNum;i++)
  {
	*pData=ntohl(pnBuf[i]);
  	pData++;
  }
  
  nNum--;
  pData=pnData;
  int nNum1=*pData;
  if(nNum!=nNum1)
  {
	  std::cout <<"Data error"<<std::endl;
	  close(sockfd); 
	  return -1;
  }
  
  close(sockfd);

  return nNum; 
}

//发送：2，个数，数据1、数据2、...；接收：平均值
//平均值作为返回值
//若函数出错，则返回0或负值。
int get_the_Avg(int nNum,int* pnData)
{
  int i,sockfd;
  struct sockaddr_in servaddr;
  
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
    return 0;
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(SERVER_PORT2);
  if(inet_aton(SERVER_ADDR2, &servaddr.sin_addr)==-1)
  	 return 0;
	
  if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
	close(sockfd); 
	return 0;
  }

  int nBuf[1024];
  nBuf[0]=htonl(2);	//函数代码,服务器可扩展成为一组功能
  nBuf[1]=htonl(nNum);
  
  int* pnData1=pnData;
  for(i=0;i<nNum;i++)
  {
	nBuf[i+2]= htonl(*pnData1);
	pnData1++;
  }
  pnData1=nBuf;
  //int nbytes=write_all(sockfd, (char*)pnData, （nNum+1)*sizeof(int));
  int nbytes=write(sockfd, (char*)pnData1, (nNum+2)*sizeof(int));
  if(nbytes<=0)
  { 
	close(sockfd); 
	return 0;
  }
  
  int nAvg;
  //nbytes=read_all(sockfd,(char*)&nAvg,sizeof(int));
  nbytes=read(sockfd,(char*)&nAvg,sizeof(int));
  if(nbytes!= sizeof(int))
  { 
	close(sockfd); 
	return 0;
  }
  
  nAvg=ntohl(nAvg);

  close(sockfd);

  return nAvg; 
}

int main()
{
  int i,nBegin,nEnd,nAvg;
  int buf[1024];
  
    std::cout <<"Please input 2 data:"<<std::endl;
    std::cin>>nBegin;
    std::cin>>nEnd;
    std::cout <<"doing..."<<std::endl;
  
    int nNum=get_the_Data(nBegin,nEnd,buf);
    if(nNum==0)
    {
	 std::cout <<"There is no any data between " <<nBegin<<"  and  "<<nEnd<<std::endl;
	 return 1;
     }else if(nNum<0){
  	 std::cout <<"There is an error."<<std::endl;
	 return 1;
    }

    std::cout <<"There is "<<nNum<<" prime number between "<<nBegin<<" and "<<nEnd<<std::endl;
    for(i=0;i<nNum;i++)
  	 std::cout <<buf[i+1]<<"\t";
	  	
    std::cout <<std::endl;
    std::cout <<std::endl;
    std::cout <<std::endl;
    std::cout <<std::endl;
   
    std::cout <<"Getting the avarage......"<<std::endl;

    nAvg=get_the_Avg(nNum,&buf[1]);
    if(nAvg<=0)
  	 std::cout <<"There is an error"<<std::endl;
    else if(nAvg==0)
    {
	 std::cout <<"The avarage cannot be gotten."<<std::endl;
	 return 1;
    }

    std::cout <<"The avg is "<<nAvg<<std::endl;
}