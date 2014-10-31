#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

int main(){
	int i;
	pid_t pid = 1;
	for(i = 0; i < 4; i++) {
		if(pid > 0) {
			pid = fork();
			if(pid == 0) {
				printf("Processo filho %d\n", getpid());
			}
		}
	}
}