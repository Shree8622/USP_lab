#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
int pid;

int main(int argc,char* argv[])
{
    int ch;
    // printf("%d %s\n",argc,argv[1]);
    int pid;
    scanf("%d",&pid);
    // printf("%d\n",pid);
    do
    {
    printf("Enter your choice\n1.Interrupt\n2.Floating pt exception\n3.Segmentation fault\n4.Illegal expression\n5.Exit\n");
    scanf("%d",&ch);
    
    if(ch==1)
    {
    printf("Sending a signal from %d to %d\n",getpid(),pid);
    kill(pid,SIGINT);
    exit(0);
    }
    else if(ch==2)
    {
    printf("Sending a signal from %d to %d\n",getpid(),pid);
    kill(pid,SIGFPE);
    exit(0);
    }
    else if(ch==3)
    {
    printf("Sending a signal from %d to %d\n",getpid(),pid);
    kill(pid,SIGSEGV);
    exit(0);
    }
    else if(ch==4)
    {
    printf("Sending a signal from %d to %d\n",getpid(),getppid());
    kill(pid,SIGILL);
    exit(0);
    }
    else
    break;
    }while(ch<5);
return 0;
}
