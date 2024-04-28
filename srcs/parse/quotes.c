# include "../../includes/minishell.h"

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] != '\0' && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (line[i] == '\"' && open == 0)
			open = 1;
		else if (line[i] == '\'' && open == 0)
			open = 2;
		else if (line[i] == '\"' && open == 1)
			open = 0;
		else if (line[i] == '\'' && open == 2)
			open = 0;
		i++;
	}
	return (open);
}
