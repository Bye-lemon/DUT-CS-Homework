#include "unistd.h"

int main(void) {
	pid_t child_pid, grandchild_pid;
	
	// This is parent process.
	child_pid = fork();
	
	if (-1 == child_pid) {
		printf("Failed to create child process!");
	} else if (0 == child_pid) {
		// This is child process.
		grandchild_pid = fork();
		
		if (-1 == grandchild_pid) {
			printf("Failed to create grandchild process!");
		} else if (0 == grandchild_pid) {
			// This is grandchild process.
			printf("I'm the grandchild process, my PID is %d.\n", getpid());
		} else {
			wait();
			printf("I'm the child process, my PID is %d, I create a grandchild process %d.\n", getpid(), grandchild_pid);
		}
	} else {
		wait();
		printf("I'm the parent process, my PID is %d, I create a child process %d.\n", getpid(), child_pid);
	}
	
	return 0;
}
