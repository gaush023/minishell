#include "../includes/minishell.h"

int	is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("><|;", line[i]))
		return (0);
	else if (ft_strchr("><|;", line[i]))
		return (1);
	else
		return (0);
}

static char	*allo_new(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	new = (char *)malloc(sizeof(char) * (i + 2 * count + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*transform_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = allo_new(line);
	while (new &&line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_free(line);
	return (new);
}

int	quote_check(t_mini *mini, char *line)
{
	if (quotes(line, INT_MAX) != 0)
	{
		ft_putstr_fd("quote error\n", STDERR);
		ft_free(line);
		mini->ret = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

void	parse(t_mini *mini)
{
	char	*line;
	t_token	*token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	if (mini->ret == 0)
		ft_putstr_fd(" 🥳 ", STDERR);
	else
		ft_putstr_fd(" 🤯 ", STDERR);
	ft_putstr_fd(M_PROMPT, STDERR);
	if (((line = readline("")) == NULL) && (mini->flag = 1))
		ft_putstr_fd("\nexit: Thank youn, bye;)\n", STDERR);
	if (g_sig.sigint == 1)
		mini->ret = g_sig.sig_flag;
	if (line == NULL || quote_check(mini, line) == 1)
		return ;
	line = transform_line(line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	mini->start = get_tokens(line, mini);
	add_history(line);
	ft_free(line);
	squish_content(mini);
	token = mini->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_token(token, 0);
		token = token->next;
	}
}

// int main(void)
//{
// char *line;
// line = ft_strdup("echo $HOME > file");
// ft_putstr_fd(line, 1);
// line = transform_line(line);
// ft_putstr_fd(line, 1);
// return (0);
//}
