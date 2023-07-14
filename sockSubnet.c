Client:
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv)
{
int sockfd,n;
char sendline[100];
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof servaddr);
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(22000);
inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
bzero( sendline, 100);
printf("Enter the ip address:");
scanf("%s",sendline);
send(sockfd,sendline,strlen(sendline),0);
printf("Enter the number of subnets:");
scanf("%d",&n);
send(sockfd,&n,sizeof(n),0);
}

Server:

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int main()
{
char str[100];
for(int i=0;i<100;i++)
str[i]='\0';
int listen_fd, comm_fd,n;
struct sockaddr_in servaddr;
listen_fd= socket(AF_INET, SOCK_STREAM, 0);
bzero( &servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htons(INADDR_ANY);
servaddr.sin_port = htons(22000);
bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
listen(listen_fd, 10);
comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
read(comm_fd,str,100);
recv(comm_fd,&n,sizeof(n),0);
char ip1[10];
for(int i=0;i<10;i++)
ip1[i]='\0';
int f1=0;
int len=strlen(str);
int nu[4],temp,num[4][8],num1[4][8],nu1[4];
for(int i=0;i<4;i++)
{
for(int j=0;j<8;j++)
{
num[i][j]=0;
num1[i][j]=0;
}
}
int sl=-1,i=0,j=0,k=0;
int t[8];
for(int l=0;l<8;l++)
t[l]=0;
while(i<len)
{
if(str[i]!='.' && str[i]!='/')
{
ip1[j]=str[i];
j++;
}
else
{
sscanf(ip1,"%d",&temp);
nu[k]=temp;
if(temp<0 || temp>255)
f1=1;
else
{
int l=0;
while(temp!=0)
{
t[l]=temp%2;
temp/=2;
l++;
}
int h=7;
for(int y=0;y<8;y++)
{
num[k][h]=t[y];
num1[k][h]=t[y];
h--;
}
}
k++;
j=0;
for(int l=0;l<10;l++)
ip1[l]='\0';
for(int l=0;l<8;l++)
{
t[l]=0;
}
}
i++;
}
sscanf(ip1,"%d",&sl);
int c=0,te=n;
while(te!=0)
{
if(te%2==1 && te!=1)
{
f1=1;
}
te/=2;
c++;
}
c--;
int ssl=sl+c;
if(sl<0 || sl>32 || k!=4 || ssl<0 || ssl>32)
f1=1;
if(f1==1)
printf("Validity = Invalid IP\n");
else
{
printf("Validity = Valid IP\n");
//Network Address
printf("Network Address = ");
int u=1;
for(int i=0;i<4;i++)
{
nu1[i]=0;
for(int j=0;j<8;j++)
{
if(u>sl)
num1[i][j]=0;
nu1[i]+=num1[i][j]*pow(2,(7-j));
u++;
}
printf("%d",nu1[i]);
if(i<3)
printf(".");
}
printf("/%d\n",sl);
//Broadcast Address
printf("Broadcast Address = ");
u=1;
for(int i=0;i<4;i++)
{
nu1[i]=0;
for(int j=0;j<8;j++)
{
if(u>sl)
num1[i][j]=1;
else
num1[i][j]=num[i][j];
nu1[i]+=num1[i][j]*pow(2,(7-j));
u++;
}
printf("%d",nu1[i]);
if(i<3)
printf(".");
}
printf("/%d\n",sl);
u=1;
for(int i=0;i<4;i++)
{
for(int j=0;j<8;j++)
{
num1[i][j]=num[i][j];
if(u>sl)
num1[i][j]=0;
u++;
}
}
//Subnetwork Address
int cl[c],bi[c];
for(int i=0;i<c;i++)
{
cl[i]=0;
bi[i]=0;
}
for(int i=0;i<n;i++)
{
int k=0;
for(int j=ssl;j>sl;j--)
{
int r=(j-1)/8;
int col=(j-1)%8;
num1[r][col]=bi[k];
cl[k]++;
int pw=pow(2,k);
if(cl[k]==pw)
{
cl[k]=0;
if(bi[k]==1)
bi[k]=0;
else
bi[k]=1;
}
k++;
}
printf("Subnetwork %d = ",i+1);
for(int a=0;a<4;a++)
{
nu1[a]=0;
for(int b=0;b<8;b++)
{
nu1[a]+=num1[a][b]*pow(2,(7-b));
}
printf("%d",nu1[a]);
if(a<3)
printf(".");
}
printf("/%d\n",ssl);
}
}
}
