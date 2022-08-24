#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
int a = mkfifo("fifo_file",0777);
// printf("%d\n",a);
int fifo = open("fifo_file",O_RDWR);
// printf("%d\n",fifo);
printf("Listening to the writer....\n");
int i=0;
char *buff[20];
for(int i=0;i<20;i++)
{
buff[i] = (char*)(malloc(20*sizeof(char)));
}
while(i<20)
{
i++;
read(fifo,buff[i],10);
printf("%s\n",buff[i]);
}
}
