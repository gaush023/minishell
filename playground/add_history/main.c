#include "../playground.h"

int main(void)
{
	char *input;

	while(1)
	{
		input = readline("Enter command> ");
		if(input == NULL)
		{
			printf("\nExiting. Bye!\n");
			break;
		}
		if(input[0] != '\0')
		{
			printf("Executing comman: %s\n", input);
			add_history(input);
		}
		free(input);
	}
	return (0);
}

	
