#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
	int pidP = getpid();
	int pid;
	for(int i=0; i<3 ; i++){

		if(getpid()==pidP){
			pid=fork();
		}
	}	
	if(pid==0){
		pid=fork();
	}
	if(pid==0){
		fork();
	}
	printf("HOLA!\n");
	wait(NULL);
}
