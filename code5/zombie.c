#include <unistd.h>
int main(int argc,char **argv)
{
	int i;
	
	printf("\n");
			
	for(i=0;i<5;i++)
		if(fork()==0)
		{
			printf("child process:%d\n",getpid());
			exit(i);
		}
	if(argc==2 && strcmp(argv[1],"-z")==0)
		for(;;){}
}
