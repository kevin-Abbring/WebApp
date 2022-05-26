#include <unistd.h>
#include <iostream>

#include<stdio.h> 
#include<stdlib.h> 
#include<errno.h> 

using namespace std;

int main(int argc,char **argv)
{
	int pipe0[2];
	int k;
	int last=0;
	int p[2];

	p[0]=-1;
	p[1]=-1;

	k=pipe(pipe0);
	cout<<"pipe0: k="<<k<<",pipe0[0]="<<pipe0[0]<<",pipe0[1]="<<pipe0[1]<<endl;
	
	int n=atoi(argv[1]);
	for(int i=0;i<n;i++)
	{
		int pipe1[2];
		int m=pipe(pipe1);
		if(m<0)
		{
			cout<<"Failed to create the "<<i<<" pipe."<<endl;
			cout<<"last="<<last<<",p[0]="<<p[0]<<",p[1]="<<p[1]<<endl;
			exit(1);
		}
		else
		{
			last++;
			p[0]=pipe1[0];
			p[1]=pipe1[1];		
		}
	}
	cout<<last<<" pipes had been created."<<endl;
	cout<<"Finished."<<endl;
	sleep(60);
	return 0;
}

