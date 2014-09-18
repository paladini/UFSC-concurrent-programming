#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

void main(){
	
	pid_t pid = 1;	
	int i = 0;
	for(i; i < 4; i++){

		if(pid > 0){
			pid = fork();
			if(pid == 0){
				printf("Processo filho %d\n", getpid());
			}
		}
	}

}
