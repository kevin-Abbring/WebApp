#include "comm_func.h"
int addr_conv(char *address,struct in_addr *inaddr)
{
	struct hostent *he;
	if(inet_aton(address,inaddr)==1)
		return (1);
	he=gethostbyname(address);
	if(he!=NULL)
	{
		*inaddr=*((struct in_addr *)he->h_addr_list[0]);
		return (1);
	}
	return 0;
}

int read_line(int fd,char *buf,int maxlen)
{
	int i,n;
	char ch;
	for(i=0;i<maxlen;)
	{
		n=read(fd,&ch,1);
		if(n==1)
		{
			buf[i++]=ch;
			if(ch=='\n')
				break;
		}
		else if(n<0)
			return (-1);
		else
			break;
	}
	buf[i]='\0';
	return (i);
}

int read_all(int fd,void *buf,int n)
{
	int nleft=n,nbytes;
	char *ptr=(char *)buf;
	for(;nleft>0;)
	{
		nbytes=read(fd,ptr,nleft);
		if(nbytes<0)
		{
			if(errno==EINTR)
				nbytes=0;
			else
				return (-1);
		}
		else if(nbytes==0)
			break;
		nleft-=nbytes;
		ptr+=nbytes;
	}
	return (n-nleft);
}

int	write_all(int fd,void *buf,int n)
{
	int nleft=n,nbytes;
	char *ptr=(char *)buf;
	for(;nleft>0;)
	{
		nbytes=write(fd,ptr,nleft);
		if(nbytes<=0)
		{
			if(errno==EINTR)
				nbytes=0;
			else
				return(-1);
		}
		nleft-=nbytes;
		ptr+=nbytes;
	}
	return (n);
}

int string_split(char *str,int *n,int nlen)
{
	char *ptr=str;
	while(*str&&nlen)
	{
		if(*str==' '||*str=='\n')
		{
			*str++=0;
			*n++=atoi(ptr);
			nlen--;
			ptr=str;
		}
		else
			str++;
	}
	return nlen;
}

int daemon_init()
{
	struct sigaction act;
	int i,maxfd,fd_rd,fd_wr;
	//1.调用fork，然后父进程退出，子进程继续运行
	if(fork()!=0)
		exit(0);
	//2.调用setsid创建新的session
	if(setsid()<0)
		return -1;
	//3.忽略信号SIGHUP，再次调用fork，然后父进程（session的头进程）退出 
	act.sa_handler=SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	if(sigaction(SIGHUP,&act,NULL)<0){
		printf("sigaction error.");
		exit(0);
	}
	if(fork()!=0)
		exit(0);
	//4.调用函数chdir（“/”），使进程不使用任何目录 
	chdir("/");
	//5.调用函数unmask（0），使进程对任何写的内容有权限 
	umask(0);
	//6.关闭所有打开的文件描述符 
	maxfd=sysconf(_SC_OPEN_MAX);//返回系统最大的文件描述符
	for(i=0;i<NOFILE;i++)
		close(i);
	//7.为标准输入（0），标准输出（1），标准错误输出（2）打开新的文件描述符 
	 
	fd_rd=open("/dev/null",O_RDONLY);
	fd_wr=open("/root/daemon.log",O_WRONLY);
	dup(fd_rd);
	dup(fd_wr);
	dup(fd_wr);
	
	//8.处理信号SIGCLD，避免守护进程的子进程成为僵尸进程
	signal(SIGCHLD, SIG_IGN);
	return 0;
}
