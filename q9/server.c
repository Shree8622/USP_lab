#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
typedef struct message
{
long type;
char msg[100];
}msg;
int main()
{
printf("Creating a request queue\n");
int req = msgget(102,IPC_CREAT|0666);
int response = msgget(101,IPC_CREAT|0666);
printf("Request queue id is 102\n");
printf("Response queue id is 101\n");
printf("Listening to the requests...\n");
msg buff;
while(1)
{
if(msgrcv(req,&buff,50,1,0)==-1)
{
printf("Error in msgrcv\n");
//exit(1);
}
else
{
printf("Request recieved!\n");
printf("Type = %ld Message = %s\n",buff.type,buff.msg);
msg t1;
t1.type=buff.type;
strcpy(t1.msg,"Responsefromserver");
msgsnd(response,&t1,50,MSG_NOERROR);
}
}
}
