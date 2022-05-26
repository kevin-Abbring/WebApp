#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <sys/epoll.h>

using namespace std;

int main(int argc, char **argv)    
{
	char c[64];
	c[0]=0x30;
	c[1]=0x31;
	c[2]=0x32;
	c[3]=0x33;
	c[4]=0x34;
	c[5]=0x35;
	c[6]=0x36;
	c[7]=0x37;
	c[8]=0x00;

	string s(c);
	cout<<s<<endl;
	//s="123456";
	cout<<"sizeof(s):"<<s.length()<<endl;
	int i=s.find('4',0);
	s=s.substr(i+1,s.length()-i-1);
	cout<<s<<endl;	
	cout<<"find:ok"<<s.find('7',0)<<endl;

	cout<<"*c("<<sizeof(c)<<"):"<<c<<endl;
}
