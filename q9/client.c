#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
struct message

{

long mtype;

char mtext[50];

};

int main()

{

int msgid,len=50;

key_t key;

struct message msg,buff;

key=102;

msgid=msgget(key,0666);
int response = msgget(101,0666);
//printf("%d\n",response);
printf("q=%d\n",msgid);

strcpy(msg.mtext,"hello world\n");
//User memory space
msg.mtype=1;
//User memory Space
len=strlen(msg.mtext);

if(msgsnd(msgid,&msg,len,0)==-1) //User to Kernel memory space

{

printf("error\n");

exit(1);

}
if(msgrcv(response,&buff,len,1,MSG_NOERROR)==-1)
{
printf("Message recieve error\n");
exit(1);
}
printf("Response = %s\n",buff.mtext);
}
