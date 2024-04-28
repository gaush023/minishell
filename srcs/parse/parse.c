# include "../../includes/minishell.h"

static int	quote_check(t_data *data, char *line)
{
	if (quotes(line, INT_MAX) != 0)
	{
		ft_putstr_fd("quote error\n", 2);
		data->ret = 2;
		data->token = NULL;
		return (1);
	}
	return (0);
}

int	parse(t_data *data)
{
	char	*line;
	t_token	*token;

	signal(SIGINT, &sig_start);
	signal(SIGQUIT, &sig_quit);

	if (data->ret == 0)
		ft_putstr_fd(SUCCESS, 2);
	else
		ft_putstr_fd(FAILURE, 2);

	line = readline(M_PROMPT);

	if ((line == NULL) && (data->continue_flag = 1))
	{
		ft_putstr_fd("\nexit: Thank youn, bye;)\n", 2);
		exit(0);
	}
	if (g_sig.sigint == 1)
		data->ret = g_sig.sig_flag;
	if (line == NULL || quote_check(data, line) == 1)
		return (1);

	line = transform_line(line);

	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);

	get_tokens(line, data);

	return (0);
	(void)token;
}
