#include "unistd.h"

int main(void) {
	pid_t child1_pid, child2_pid;
	
	child1_pid = fork();
	
	if (-1 == child1_pid) {
		printf("Failed to create child 1 process!");
	} else if (0 == child1_pid) {
		// This is child 1 process.
		printf("I'm the child 1 process, my PID is %d.\n", getpid());
	} else {
		wait();
		
		child2_pid = fork();
		
		if (-1 == child2_pid) {
			printf("Failed to create child 2 process!");
		} else if (0 == child2_pid) {
			// This is child 2 process.
			sleep(0.2);
			printf("I'm the child 2 process, my PID is %d.\n", getpid());
		} else {
			wait();
			printf("I'm the parent process, my PID is %d, I create two child processes %d and %d.\n", getpid(), child1_pid, child2_pid);
		}
	}
	
	return 0;
} 
