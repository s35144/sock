#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>

int main(){
	int n,socfd;
	char sendln[100],recvln[100];
	struct sockaddr_in serv;
	
	socfd=socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serv, sizeof(serv));
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(22000);
	inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
	
	connect(socfd,(struct sockaddr *) &serv, sizeof(serv));
	
	while(1){
		bzero(sendln,100);
		bzero(recvln,100);
		
		fgets(sendln,100,stdin);
		write(socfd, sendln, strlen(sendln)+1);
		read(socfd, recvln, 100);
		printf("Received wword : %s\n",recvln);
	}
	return 0;
}
