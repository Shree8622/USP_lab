#include<stdio.h>
#include<unistd.h>

int main()
{
    int val = fork();
    if(val==0)
    {
        printf("Process id = %d Parent process id = %d\n",getpid(),getppid());
        printf("Enter the command\n");
        char t[10];
        scanf("%s",t);
        system(t);
    }
    else
    {
        wait();
        printf("Child id = %d Process id = %d \n",val,getpid());
    }
}