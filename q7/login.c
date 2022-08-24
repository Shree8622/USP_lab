#include<stdio.h>
#include<shadow.h>
#include<crypt.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/stat.h>

char* get_salt(char* shadow_entry)
{
    // Extracting salt from the shadow entry
    int count=0,j=0;
    char* salt = (char*)malloc(sizeof(char)*50);
    while(j<strlen(shadow_entry))
    {
        if(shadow_entry[j]=='$')
        {
            count++;
        }
        salt[j]=shadow_entry[j];
        j++;
        if(count==4)
        break;
    }
    return salt;
}
int authn(char *usr,char* pwd)
{
    char s[100];
    struct spwd *a=NULL;
    a = getspnam(usr);
    if(a!=NULL)
    {
        char *salt = get_salt(a->sp_pwdp);
        return strcmp(a->sp_pwdp,crypt(pwd,salt));
    }
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
    int pid=0;
    int j=0;
    while(buff[j]!=' ')
    {
        pid+=buff[j]-'0';
        pid*=10;
        j++;
    }
    pid/=10;
    j++;
    //printf("Entry recieved: %s\n",buff);
    char *p_ = strtok(buff," ");
    char *file = strtok(NULL," ");
    char *usr = strtok(NULL," ");
    char *pwd = strtok(NULL,"\n");
    //printf("user:%s\n",usr);
    //printf("pwd: %s\n",pwd);
   // printf("Pid of the process: %d\n",pid);
    //printf("Authenticating..\n");
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
    mkfifo("fifo",0666);
    // printf("%d\n",getpid());
    rdr = open("fifo",O_RDONLY);
    printf("Reading log entries...\n");
    while(1)
    {
        read(rdr,buff,30);
        if(strlen(buff))
        {
            //printf("Buffer: %s\n",buff);
            sig_hand();
            for(int i=0;i<50;i++) //clean buffer
                buff[i]='\0';
        } 
    }

}
