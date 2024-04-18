#include "includes/minishell.h"

t_sig	g_sig;

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

void	is_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	redirect(t_mini *mini, t_token *token, int type)
{
	is_close(mini->fdout);
	if (type == REDIR)
		mini->fdout = open(token->next->content, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRWXU);
	else if (type == APPEND)
		mini->fdout = open(token->next->content, O_WRONLY | O_CREAT | O_APPEND,
				S_IRWXU);
	if (mini->fdout < 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->content, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

void	input(t_mini *mini, t_token *token)
{
	is_close(mini->fdin);
	mini->fdin = open(token->next->content, O_RDONLY);
	if (mini->fdin < 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->content, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}

int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		ft_panic(mini, "Error: pipe", err_pipe);
	if ((pid = fork()) < 0)
		ft_panic(mini, "Error: fork", err_fork);
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->pipein = pipefd[0];
		mini->m_pid = -1;
		mini->parent = 0;
		mini->no_exec = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipeout = pipefd[1];
		mini->m_pid = pid;
		mini->last = 0;
		return (1);
	}
}

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, SKIP);
	next = next_sep(token, SKIP);
	pipe = 0;
	if (is_type(token, REDIR))
		redirect(mini, token, REDIR);
	else if (is_type(token, APPEND))
		redirect(mini, token, APPEND);
	else if (is_type(token, INPUT))
		input(mini, token);
	else if (is_type(token, PIPE))
		pipe = minipipe(mini);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev) && pipe != 1
		&& mini->no_exec == 0)
		exec_cmd(mini, token);
}

void	minishell(t_mini *mini)
{
	t_token	*token;

	
	int		status;

	token = next_run(mini->start, NOSKIP);
	if (is_types(token, "TAI"))
		token = mini->start->next;
	while (mini->flag == 0 && token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		redir_and_exc(mini, token);
	}
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q minishell");
}

void	mini_init(t_mini *mini)
{
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	if (!mini->in || !mini->out)
		ft_panic(NULL, "dup", 1);
	mini->flag = 0;
	mini->ret = 0;
}

int	main(int ac, char **av, char **ev)
{
	t_mini	mini;
	t_token	*tmp;

	(void)ac;
	(void)av;
	mini_init(&mini);
	reset_fds(&mini);
	env_init(&mini, ev);
	secret_env_init(&mini, ev);
	get_shlvl_plus(mini.env);
	while (mini.flag == 0)
	{
		ini_sig();
		parse(&mini);
		if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
		while (mini.start)
		{
			free(mini.start->content);
			tmp = mini.start->next;
			free(mini.start);
			mini.start = tmp;
		}
	}
	free_all(&mini, 0);
	sleep(1);
}
