#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/time.h>
char *name;

void display_file()
{
    char cmd[100];
    printf("Displaying the file contents\n");
    strcpy(cmd,"cat ");
    strcat(cmd,name);
    printf("%s\n",cmd);
    system(cmd);
    printf("\nExiting...\n");
    exit(0);
}
void auth_fail()
{
    printf("Authentication failed!\nExiting...\n");
    exit(0);
}
int main(int argc,char* argv[])
{
    signal(SIGUSR1,display_file);
    signal(SIGUSR2,auth_fail);

    int wrt = open("fifo",O_WRONLY);

    printf("Enter the file path you want to access\n");
    char path[20];
    scanf("%s",path);
    name=path;
    char *pwd = strdup(getpass("Password: ")); 
    
    char msg[40];
    int pid = getpid();
    char pid_str[10];
    sprintf(pid_str,"%d",pid);
    strcat(msg,pid_str);
    strcat(msg," ");

    char *user = getlogin();
    strcat(msg,user);
    strcat(msg," ");

    strcat(msg,pwd);

    write(wrt,msg,strlen(msg));
    while(1)
    {
    }
}
