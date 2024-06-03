#include "../includes/minishell.h"

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



int	check_line(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_types(token, "HTAI") && (!token->next || is_types(token->next,
					"TAIPE")))
		{
			ft_putstr_fd(" minishell: syntax error near unexpected token `",
					STDERR);
			if (token->next)
				ft_putstr_fd(token->next->content, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putstr_fd("'\n", STDERR);
			mini->ret = 258;
			return (0);
		}
		if (is_types(token, "PE") && (!token->prev || !token->next || is_types(token->prev,
					"TAIPE")))
		{
			ft_putstr_fd(" minishell: syntax error near unexpected token `",
					STDERR);
			ft_putstr_fd(token->content, STDERR);
			write(STDERR, "'\n", 2);
			mini->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

