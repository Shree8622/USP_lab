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
    int file = open(name,O_RDONLY);
    char c[100];
    printf("Displaying the file contents\n");
    while(1)
    {
        
        int t = read(file,c,100);
        printf("%s",c);
        if(t<100)
            break;
    }
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
    char str[40];
    int pid = getpid(),temp=pid,n=1;
    while(temp>1)
    {
        temp/=10;
        if(temp)
        n*=10;
    }
    
    int i=0;
    for(;n>0;i++)
    {
        str[i]= '0' + pid/n;
        pid%=n;
        n/=10;
    }
    str[i++]=' ';
    for(int j=0;j<strlen(path);j++)
    {
        str[i+j]=path[j];
    }
    i+=strlen(path);
    str[i++]=' ';
    char *a = getlogin();
    for(int j=0;j<strlen(a);j++)
    {
        str[i+j]=a[j];
    }
    i+=strlen(a);
    str[i++]=' ';
    
    for(int j=0;j<strlen(pwd);j++)
    {
        str[i+j]=pwd[j];
    }
    // printf("%s\n",str);
    write(wrt,str,strlen(str));
    while(1)
    {

    }
}
