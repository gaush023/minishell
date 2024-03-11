#include "../../includes/minishell.h"

int main(void)
{
	pid_t id;
	
	id = fork();
	if(id == 0)
		printf("I am the child process\n");
	else if(id > 0)
		printf("I am the parent process\n");
	else
		printf("The fork failed\n");
	return (0);
}