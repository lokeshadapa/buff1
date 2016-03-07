#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
int main()
{
	char *buf=new char[1024];
	//scanf("%s",buf);
	while(1)
	{
		int n=read(0,buf,1024);
		for(int i=0;i<n;i++)
		{
			buf[i]=toupper(buf[i]);
		}
		write(1,buf,1024);
	}
}
