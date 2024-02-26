#include <stdio.h>

int main(int ac, char **av, char **env)
{
	int i = 0;
	(void)ac;
	(void)av;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

