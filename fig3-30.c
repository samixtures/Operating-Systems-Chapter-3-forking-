/*
 * Figure 3.30
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int value = 5;

int main()
{
	pid_t pid;

	pid = fork();
	
	if (pid == 0) { /* child process */
		value += 15;
		printf("in child, value is: %d\n", value); //%d is decimal (base 10 like we learned in assembly)
		return 0;
	}
	else if (pid > 0) { /* parent process */
		wait(NULL);
		printf ("PARENT: value not changed, value still = %d\n",value); /* LINE A */
		return 0;
	}
}
