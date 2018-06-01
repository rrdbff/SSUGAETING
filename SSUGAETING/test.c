#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
	
#define BUF_SIZE 100
#define NAME_SIZE 20
	
//void * send_msg(void * arg);
//void * recv_msg(void * arg);
void error_handling(char * msg);
	
char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];
	
int main(int argc, char *argv[])
{
	int sock;
    char msg[1024]="POST / HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nUser-Agent: Dalvik/2.1.0\r\nHOST: 192.168.0.5:1234\r\nConnection: Keep-Alive\r\nAccept-Encoding: gzip\r\nContent-Length: 12\r\n\r\nheader=0$id=asdf\n";
    char rcvbuf[1024];
	struct sockaddr_in serv_addr;
	pthread_t snd_thread, rcv_thread;
	void * thread_return;
	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	 }
	
	//sprintf(name, "[%s]", argv[3]);
	sock=socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	  
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error");
    write(sock,msg,sizeof(msg));
    read(sock,rcvbuf,1024);
    
    printf("%s",rcvbuf);
    close(sock);
    return 0;
		
}
void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
