#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "http-parser.h"


#define BUF_SIZE 2048
#define SMALL_BUF 128

void* request_handler(void *arg)
{
    int clnt_sock=*((int*)arg);
    http_request_line_t req_line= {0,};
    http_header_fields_t fields = {0,};
    FILE* clnt_read;
    FILE* clnt_write;
    char buf[BUF_SIZE];
    char header[BUF_SIZE];
    char message[BUF_SIZE];
    char buf[SMALL_BUF];
    char ct[15];

    clnt_read = fdopen(clnt_sock, "r");
    clnt_write = fdopen(dup(clnt_sock), "w");
    while(1)
    {
        fgets(buf,BUF_SIZE,clnt_read);
        strcat(header,buf);
        if(strstr(buf,"\r\n\r\n"))
            break;
    }
    while(1)
    {
        fscanf_s(clnt_read,"%s",&message,SMALL_BUF);
        if(feof(clnt_read))
            break;
    }
    parseHttpHeader(parseHttpRequestLine(header, &req_line), &fields);
    

    strcpy(ct, content_type(header));
    fclose(clnt_read);
    send_data(clnt_write, ct, req_line.uri);
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

void parse_message(char* message, size_t msglen)
{
    switch(message[0])
        case '0' :
        
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
            
}

