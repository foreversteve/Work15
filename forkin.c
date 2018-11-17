#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
	srand(time(NULL));
	int f;
	int arr[2];
	arr[0] = rand();
	arr[1] = rand();

	f = fork();
	if (!f){
		printf("Process %d is sleeping...\n",getpid());
		int rval = (arr[0] % 16)+5;
		sleep(rval);
		if (getppid() != 1){
			printf("Process %d Finished after: %d seconds\n",getpid(),rval);
		}
		return rval;
	}
	else{
		int f;
		f = fork();
		if (!f){
			printf("Process %d is sleeping...\n",getpid());
			int rval = (arr[1] % 16)+5;
			sleep(rval);
			if (getppid() != 1){
				printf("Process %d Finished after: %d seconds\n",getpid(),rval);
			}
			return rval;
		}
		else{
			int status;
			int pid = wait(&status);
			printf("Parent Process Complete... Process %d slept for %d seconds\n",pid,WEXITSTATUS(status));
			return 0;
		}
		
	}

	return 0;

}