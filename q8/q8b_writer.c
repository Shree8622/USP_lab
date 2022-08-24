#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{

int fifo = open("fifo_file",O_WRONLY);
int i=10;
printf("Write data to the pipe!\n");
while(1)
{
char a[20];
scanf("%s",a);
write(fifo,a,strlen(a));
//sleep(1000);
}

}
