#include "../playground.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("Enter command> ");
		printf("input: %s\n", input);
		printf("input[0]: %c\n", input[0]);
		if (input == NULL)
		{
			printf("\nExiting. Bye!\n");
			break ;
		}
		if (input[0] != '\0')
		{
			printf("Executing comman: %s\n", input);
			add_history(input);
		}
		free(input);
	}
	return (0);
}
