#include "../includes/minishell.h"

void	here_doc(t_mini *mini, t_token *token)
{
	char *delimiter;
	char *line;
	t_token *tmp;

	g_sig.heredoc_flag = 1;
	delimiter = token->content;
	mini->heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (mini->heredoc_fd == -1)
		return ;
	while (1)
	{
		if(g_sig.sigint != 1)
			ft_putstr_fd("> ", 1);
		line = readline(" \b");
		printf("here_doc:2\n");
		if (g_sig.sigint == 1)
		{
			line = transform_line(line);
			tmp = get_tokens(line);
			printf("line: %s\n", line);
			token->prev->next = tmp;
			break ;
		}
		printf("here_doc:3\n");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
			{
				ft_putstr_fd("\n", 1);
				ft_close(mini->heredoc_fd);
				return ;
			}
			ft_free(line);
			break ;
		}
		printf("here_doc:4\n");
		ft_putstr_fd(line, mini->heredoc_fd);
		ft_putstr_fd("\n", mini->heredoc_fd);
		ft_free(line);
		printf("here_doc:5\n");
	}
	ft_close(mini->heredoc_fd);
	if (g_sig.sigint != 1)
		mini->heredoc_fd = open("/tmp/heredoc_tmp", O_RDONLY);
	else
		mini->heredoc_fd = open("/dev/null", O_RDONLY);
	if (mini->heredoc_fd == -1)
		return ;
	dup2(mini->heredoc_fd, STDIN);
	ft_close(mini->heredoc_fd);
	if (g_sig.sigint != 1)
		g_sig.heredoc_flag = 0;
}