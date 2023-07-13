#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){
	int listenfd, comm;
	char str[100];
	struct sockaddr_in serv;
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&serv,sizeof(serv));
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(22000);
	serv.sin_addr.s_addr = htons(INADDR_ANY);
	
	bind(listenfd, (struct sockaddr *)&serv, sizeof(serv));
	listen(listenfd, 10);
	comm=accept(listenfd,NULL,NULL);
	
	while(1){
		bzero(str, 100);
		
		read(comm, str, 100);
		printf("Writing back : %s\n",str);
		write(comm, str, strlen(str)+1);
		
	}
	return 0;
}
