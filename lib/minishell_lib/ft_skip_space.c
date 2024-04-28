# include "./minishell_lib.h"

void	ft_skip_space(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
}
