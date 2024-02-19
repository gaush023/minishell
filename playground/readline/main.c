#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *input;

	input = readline("Enter your command: ");
	if(input != NULL)
	{
		printf("You enterd: %s\n", input);
		add_history(input);
		free(input);
	}
	return (0);
}	

