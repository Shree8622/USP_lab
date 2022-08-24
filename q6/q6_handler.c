#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void interrupt()
{
    printf("In process %d \n",getpid());
    printf("Terminating process %d\n",getpid());
    exit(0);
}
void floating_pt_exception()
{
    printf("In process %d \n",getpid());
    printf("Terminating process %d\n",getpid());
    exit(0);
}
void seg_fault()
{
    printf("In process %d \n",getpid());
    printf("Terminating process %d\n",getpid());
    exit(0);
}
void illegal_inst()
{
    printf("In process %d \n",getpid());
    printf("Terminating process %d\n",getpid());
    exit(0);
}
int main()
{
    signal(SIGINT,interrupt);
    signal(SIGFPE,floating_pt_exception);
    signal(SIGSEGV,seg_fault);
    signal(SIGILL,illegal_inst);
    printf("%d\n",getpid());
    while(1)
    {

    }

}
