#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>
int main(char** abc)
{
		int pid=atoi(abc[0]);
		char ch;
        long int idk= syscall(317, pid, abc[1]);
        if(idk==0){
        	printf("system call ran successfully\n");
        }
        else{
        	printf("System call didn't execute properly\n");
        	perror("error");
        	printf("Error no: %d\n", errno);
        }
        return 0;
}