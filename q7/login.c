#include<stdio.h>
#include<shadow.h>
#include<crypt.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/stat.h>

int authn(char *usr,char* pwd)
{
    char s[100];
    struct spwd *a=NULL;
    a = getspnam(usr);
    if(a!=NULL)
        return strcmp(a->sp_pwdp,crypt(pwd,a->sp_pwdp));
    else
    {
        printf("Shadow entry not found!\n");
    }
    return -1;
}
int rdr;
char buff[50];
void sig_hand()
{   
    char *pid_str = strtok(buff," ");
    char *usr = strtok(NULL," ");
    char *pwd = strtok(NULL,"\n");
    
    int pid=atoi(pid_str);
    if(!authn(usr,pwd))
    {
        printf("Authentication sucessfull!\n");
        kill(pid,SIGUSR1);
    }
    else
    {
        printf("Authentication failed!\n");
        kill(pid,SIGUSR2);
    }
}
int main()
{
    int ret = fork();
    if(ret==0)
    {
        if( setsid()<0 ) { //failed to become session leader
        fprintf(stderr,"error: failed setsid\n");
        exit(EXIT_FAILURE);
        }

        signal(SIGCHLD,SIG_IGN);
        signal(SIGHUP,SIG_IGN);

        int child;
        if ( (child=fork())<0) { //failed fork
            fprintf(stderr,"error: failed fork\n");
            exit(EXIT_FAILURE);
        }
        if( child>0 ) { //parent
            exit(EXIT_SUCCESS);
        }
    
        mkfifo("fifo",0666);
        rdr = open("fifo",O_RDONLY);
        printf("Reading log entries...\n");
        while(1)
        {
            read(rdr,buff,30);
            if(strlen(buff))
            {
                sig_hand();
                strcpy(buff,"");
            } 
        }
    }
}
