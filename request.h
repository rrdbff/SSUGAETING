#ifndef __REQUEST_H__
#define __REQUEST_H__
typedef struct user_info{
    char* id;
    char* password;
    char* name;
    char* email;
    char* sex;
    char* age;
    char* imageURL;
    char* statusmsg;
    char* height;
    char* address;
    char* major;
    char* religion;
    char* hobby;
    char* college;
    char* club;
    char* abroadexp;
    char* milserv;
}user_info;
typedef struct chat{
    char* s_id;
    char* d_id;
    char* textmsg;
    char* acceptance;
    FILE* image;
}chat;
extern void* request_handler(void* arg);
extern void send_data(FILE* fp, char* ct, char* file_name);
extern char* content_type(char* file);
extern void send_error(FILE* fp);
extern void error_handling(char* message);
extern void parse_message(char* message, user_info* user, chat* d_user);
