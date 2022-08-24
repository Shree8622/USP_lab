#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
int main()
{
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    int val = fork();
    if (val == 0)
    {
        printf("In child process\n");
        printf("Enter some data\n");
        char s[20];
        // getchar();
        scanf("%s", s);
        printf("Entered in child: %s\n",s);
        int nb;
        nb = write(p1[1], s, strlen(s));
        if(nb)
            printf("write successful\n");
        //exit(0);
    }
    else
    {
        printf("Parent process waiting for msg\n");
        // wait(NULL);
        printf("%d %d",p2[0],p2[1]); 
        fd_set rd_set;
        fd_set wr_set;
        struct timeval t;
        int retval;

        FD_ZERO(&rd_set);
        FD_ZERO(&wr_set);
        FD_SET(p1[0], &rd_set);
        FD_SET(p2[0], &rd_set);
        FD_SET(p1[1], &wr_set);
        FD_SET(p2[1], &wr_set);
        t.tv_sec = 5;
        t.tv_usec = 0;

        printf("%d %d",p2[0],p2[1]); 

            int ret_val = select(p2[1]+1, &rd_set, NULL, NULL, &t);
            // printf("%d\n",ret_val);
            char buff[30];
                
                if(ret_val)
                {
                    if(FD_ISSET(p1[0],&rd_set))
                    {
                        read(p1[0], buff, 10);
                        printf("Message recieved from 1!!\n");
                        
                    }
                    else if(FD_ISSET(p2[0],&rd_set))
                    {
                        read(p2[0], buff, 10);
                        printf("Message recieved from 2!!\n");
                    }
                    printf("buffer: %s\n", buff);
                }    
                
                // FD_ZERO(&wr_set);
        exit(0);
    }
}
