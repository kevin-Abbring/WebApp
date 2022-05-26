#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char **argv)
{
	struct hostent *he;
	int i=0;
	int fd;
	char buf[256];
	if(argc<2)
	{
		printf("Usage: %s ip/domainname [filename]\n",argv[0]);
		return 1;
	}

	//---ip-------------------------------
	struct in_addr addr;
	if(inet_aton(argv[1],&addr) != 0)
	{
		he=gethostbyaddr((char *)&addr,4,AF_INET);
		if(he!=NULL)
			printf("h_name:%s\n",he->h_name);
		else
			printf("gethostbyaddr error:%s\n",hstrerror(h_errno));
	}
	else
	{
	//---domain-------------------------------
		he=gethostbyname(argv[1]);
		if(he!=NULL)
		{
			printf("h_name:%s\n",he->h_name);
			printf("h_length:%d\n",he->h_length);
			printf("h_addrtype:%d\n",he->h_addrtype);
			for(i=0;he->h_aliases[i]!=NULL;i++)
				printf("h_aliases[%d]:%s\n",i+1,he->h_aliases[i]);
			printf("first ip:%s\r\n",inet_ntoa(*((struct in_addr *)he->h_addr)));

			for(i=0;he->h_addr_list[i]!=NULL;i++)
				printf("ip%d:%s\n",i+1,inet_ntoa(*(struct in_addr *)he->h_addr_list[i]));

			if(argc==3)
			{
				if((fd=open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))!=-1)
				{
					sprintf(buf,"h_name:%s\n",he->h_name);
					write(fd,buf,strlen(buf));
					sprintf(buf,"h_length:%d\n",he->h_length);
					write(fd,buf,strlen(buf));
					sprintf(buf,"h_addrtype:%d\n",he->h_addrtype);
					write(fd,buf,strlen(buf));
					for(i=0;he->h_aliases[i]!=NULL;i++)
					{
						sprintf(buf,"h_aliases[%d]:%s\n",i+1,he->h_aliases[i]);
						write(fd,buf,strlen(buf));
					}
			
					sprintf(buf,"first ip:%s\r\n",inet_ntoa(*((struct in_addr *)he->h_addr)));
					write(fd,buf,strlen(buf));
					for(i=0;he->h_addr_list[i]!=NULL;i++)
					{
						sprintf(buf,"ip%d:%s\n",i+1,inet_ntoa(*(struct in_addr *)he->h_addr_list[i]));
						write(fd,buf,strlen(buf));
					}
				}
				else
					printf("open file error:%s\n",hstrerror(h_errno));
			}
		}
		else
			printf("gethostbyname error:%s\n\n",hstrerror(h_errno));
	}
}

