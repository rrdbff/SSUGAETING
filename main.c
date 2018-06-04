#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "request.h"


#define TRUE 1
#define FALSE 0
#define BUF_SIZE 4096
#define SMALL_BUF 128
void* request_handler2(void *arg);
void error_handling2(char* message);

int main(int argc, char *argv[])
{
    
    
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    pthread_t t_id;
    int option;
    char ss[BUF_SIZE]; //k
 
    socklen_t optlen,clnt_adr_size;
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    optlen=sizeof(option);
    option = TRUE;
    setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen);
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling2("bind() error");
    if(listen(serv_sock,20)==-1)
        error_handling2("listen() error");
    
    while(1)
    {
        clnt_adr_size=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size);
       // printf("A");
        printf("Connection Request : %s:%d\n", inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));

       int a =pthread_create(&t_id,NULL,request_handler,&clnt_sock);
       //      char* msg ="OK/r/n";
       
       //      read(clnt_sock,ss,sizeof(ss));
       //      printf("%s",ss);
 

      pthread_detach(t_id);
    }
   
    close(serv_sock);
    return 0;
}

void* request_handler2(void *arg)
{
       char response_packet[1024] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nContent-Type:text/plain\r\n\r\nOK";
    int clnt_sock=*((int*)arg);
        char ss[BUF_SIZE]; 
        read(clnt_sock,ss,sizeof(ss));
        printf("%s",ss);
        write(clnt_sock,response_packet,sizeof(response_packet));
        printf("%s\n",response_packet);
        printf("BSBS");
        puts("ok sent");

//   http_request_line_t req_line= {0,};
//   http_header_fields_t fields = {0,}; 
//   user_info user={0,};
//   chat chatinfo={0,};
//     FILE* clnt_read;
//     FILE* clnt_write;
// //    char buf[BUF_SIZE];
// //    char header[BUF_SIZE];
//     char* message;
// //    char ct[15];
//     
//     if((clnt_read = fdopen(clnt_sock, "r"))==NULL)
//         error_handling2("fdopen() fail");
//     clnt_write = fdopen(dup(clnt_sock), "w");
// //     while(1)
// //     {
// //         fgets(buf,BUF_SIZE,clnt_read);
// //         strcat(header,buf);
// //         printf("%s",header);
// //         if(strstr(buf,"\r\n\r\n"))
// //             break;
// //     }
//      fputs("c",stdout);
//     while(1)
//     {
//         fscanf(clnt_read,"%s",message);
//         if(feof(clnt_read))
//             break;
//     }
//     printf("%s",message);
//     parseHttpHeader(parseHttpRequestLine(header, &req_line), &fields);
//     parse_message(message, &user, &chatinfo);
//     printf("a");
//     strcpy(ct, content_type(header));
//     fclose(clnt_read);
//     
//     printf("id : %s\n",user.id);
  //  send_data(clnt_write, ct, req_line.uri);
}

void error_handling2(char* message)
{
    fputs(message,stderr);
    fputs("\n",stderr);
    exit(1);
}
    
    
