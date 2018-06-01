#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "http-parser.h"
#include "request.h"



#define BUF_SIZE 2048
#define SMALL_BUF 128

void* request_handler(void *arg)
{
    char response_packet[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nContent-Type:text/plain\r\n\r\nOK&";
    int clnt_sock=*((int*)arg);
        char ss[BUF_SIZE]; 
        read(clnt_sock,ss,sizeof(ss));
        printf("%s",ss);
        write(clnt_sock,response_packet,sizeof(response_packet));
        printf("%s\n",response_packet);
        puts("ok sent");
        puts("BSBS");
//     http_request_line_t req_line= {0,};
//     http_header_fields_t fields = {0,};
//     user_info user={0,};
//     chat chatinfo={0,};
//     FILE* clnt_read;
//     FILE* clnt_write;
//     char buf[BUF_SIZE];
//     char header[BUF_SIZE];
//     char message[5120];
//     char ct[15];
//  
//     clnt_read = fdopen(clnt_sock, "r");
//     clnt_write = fdopen(dup(clnt_sock), "w");
//     while(1)
//     {
//         fgets(buf,BUF_SIZE,clnt_read);
//         strcat(header,buf);
//         printf("%s",header);
//         if((strstr(buf,"\r\n\r\n"))==NULL)
//             break;
//     }
//     fputs("c",stdout);
//  //   while(1)
//  //   {
//         fscanf(clnt_read,"%s",message);
//         puts("message read");
// //        if(feof(clnt_read))
// //            break;
// //    }
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

void send_data(FILE* fp, char* ct, char* file_name)
{
    char protocol[]="HTTP/1.0 200 OK\r\n";
    char server[]="Server:Linux Web Server \r\n";
    char cnt_len[]= "Content-length:2048\r\n";
    char cnt_type[SMALL_BUF];
    char buf[BUF_SIZE];
    FILE* send_file;
    
    sprintf(cnt_type, "Content-type:%s\r\n\r\n",ct);
    send_file=fopen(file_name,"r");
    if(send_file==NULL)
    {
        send_error(fp);
        return;
    }

    fputs(protocol,fp);
    fputs(server,fp);
    fputs(cnt_len,fp);
    fputs(cnt_type,fp);
    
    while(fgets(buf,BUF_SIZE,send_file)!=NULL)
    {
        fputs(buf,fp);
        fflush(fp);
    }
    fflush(fp);
    fclose(fp);
    
}

char* content_type(char* file)
{
    char extension[SMALL_BUF];
    char file_name[SMALL_BUF];
    strcpy(file_name, file);
    strtok(file_name, ".");
    strcpy(extension,strtok(NULL, "."));
    if(!strcmp(extension, "html")||!strcmp(extension, "htm"))
        return "text/html";
    else if (!strcmp(extension, "gif" ))
        return "image/gif";
    else if (!strcmp(extension, "jpeg"))
        return "image/jpeg";
    else 
        return "text/plain";
    
}

void send_error(FILE* fp)
{
    char protocol[]="HTTP/1.0 400 Bad Request\r\n";
    char server[]="Server:Linux Web Server \r\n";
    char cnt_len[]= "Content-length:2048\r\n";
    char cnt_type[]= "Content-type:text/html\r\n\r\n";
    char content[]="<html><head><title>NETWORK</title></head><body><font size=+5><br>error!! check request-filetype & request-method!</font></body></html>";
    
    fputs(protocol,fp);
    fputs(server,fp);
    fputs(cnt_len,fp);
    fputs(cnt_type,fp);
    fflush(fp);
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputs("\n",stderr);
    exit(1);
}

void parse_message(char* message, user_info* user, chat* chatinfo)
{
    char* header;
    switch(message[0])
    {
        case '0' :      //id repetition check message
            header = strtok(message,"$");
            user->id = strtok(NULL,"$");
        
        case '1' :      //create account message
            header = strtok(message,"$");
            user->id = strtok(NULL,"$");
            user->password = strtok(NULL,"$");
            user->name =strtok(NULL,"$");
            user->email = strtok(NULL,"$");
            user->sex = strtok(NULL,"$");
        case '2' :      //login id/pw message
            header = strtok(message,"$");
            user->id = strtok(NULL,"$");
            user->password = strtok(NULL,"$");
        case '3' :      //email check message to find id
            header = strtok(message,"$");
            user->email = strtok(NULL,"$");
        case '4' :      //email/id check message to find pw
            header = strtok(message,"$");
            user->id = strtok(NULL,"$");
            user->email = strtok(NULL,"$");
        case '5' :      //user matching request message
            header = strtok(message,"$");
            chatinfo->s_id = strtok(NULL,"$");
            chatinfo->d_id = strtok(NULL,"$");
        case '6' :      //user matching response message
            header = strtok(message,"$");
            chatinfo->s_id = strtok(NULL,"$");
            chatinfo->d_id = strtok(NULL,"$");
            chatinfo->acceptance = strtok(NULL,"$");
        case '7' :      //update profile message
            header = strtok(message,"$");   
            user->id=strtok(NULL,"$");
            user->password=strtok(NULL,"$");
            user->email= strtok(NULL,"$");
            user->name= strtok(NULL,"$");
            user->sex= strtok(NULL,"$");
            user->statusmsg= strtok(NULL,"$");
            user->age= strtok(NULL,"$");
            user->height= strtok(NULL,"$");
            user->address= strtok(NULL,"$");
            user->hobby= strtok(NULL,"$");
            user->college= strtok(NULL,"$");
            user->major= strtok(NULL,"$");
            user->imageURL= strtok(NULL,"$");
            user->religion= strtok(NULL,"$");
            user->club= strtok(NULL,"$");
            user->abroadexp= strtok(NULL,"$");
            user->milserv= strtok(NULL,"$");
        case '8' :      //chat : send image
            header = strtok(message,"$");
            chatinfo->s_id = strtok(NULL,"$");
            chatinfo->d_id = strtok(NULL,"$");
            int fd;
            char* temp=strtok(NULL,"$");
            if (0<(fd=creat("image.jpg",0644)))
            {
                write(fd,temp,strlen(temp));
                close(fd);
            }
            else
            {
                printf("file create fail");
            }
  //      case '9':       //chat : send txt
    }
}

