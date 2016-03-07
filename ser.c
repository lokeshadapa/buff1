#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<stdlib.h>
typedef struct sockaddr_in sckadr;
int main(int argc,char **argv)
{
	int port=atoi(argv[1]);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd<0)
	printf("socket failed\n");
	sckadr seradr;
	seradr.sin_family=AF_INET;
	seradr.sin_port=htons(port);
	seradr.sin_addr.s_addr=htonl(INADDR_ANY);
	bzero(seradr.sin_zero,8);
	int m=bind(sfd,(struct sockaddr *)&seradr,sizeof(seradr));
	if(m<0)
	printf("bind failed");
	socklen_t clen;
	sckadr cadr;
	int n=listen(sfd,1);
	int pid;
	char *buf=new char[1024];
	while(1)
	{
		int nsfd=accept(sfd,(struct sockaddr *)&cadr,&clen);
		if(nsfd>=0)
		{
			printf("entered\n");
			pid=fork();
			if(pid==0)
			{
				close(sfd);
				int r=recv(nsfd,buf,1024,0);
				printf("requested service :%s\n",buf);
				dup2(nsfd,0);
				dup2(nsfd,1);
				execlp(buf,buf,(char *)0);
			}
			else
			{
				close(nsfd);
			}
		}
	}
}

