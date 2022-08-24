#include<stdio.h>
#include<stdlib.h>
#include<setjmp.h>

void func1(jmp_buf t)
{
    longjmp(t,1);
}
void func2(jmp_buf t)
{
    longjmp(t,2);
}
int main()
{
    jmp_buf a;
    int val = setjmp(a);
    if(val!=0)
    {
        switch(val)
        {
            case 1: printf("Function called: func1 \n");
            break;
            case 2: printf("Function called: func2\n");
            break;
            default: break;
        }
        exit(0);
    }
    func2(a);
}