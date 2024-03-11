#include "../includes/minishell.h"

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < SEMICOLON)
			token = token->next;
	}
	return (token);
}

void is_close(int fd)
{
	if(fd > 0)
		close(fd);
}

void redir(t_mini *mini, t_token *token, int type)
{
	is_close(mini->fdout);
	if(type == REDIR)
		mini->fdout = open(token->next->content, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if(type == APPEND)
		mini->fdout = open(token->next->content, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if(mini->fdout < 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->content, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->ret = 1;
		mini->no_exec	= 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

void input(t_mini *mini, t_token *token)
{
	is_close(mini->fdin);
	mini->fdin = open(token->next->content, O_RDONLY);
	if(mini->fdin < 0)
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


void redir_and_exec(t_mini *mini, t_token *token)
{
	t_token *prev;
	t_token *next;	
	int pipe;	

	prev = prev_sep(token, SKIP);
	next = next_sep(token, SKIP);
	pipe = 0;	
	if(is_type(token, REDIR))
		redirect(mini, token, REDIR);
	else if(is_type(token, APPEND))
		redirect(mini, token, APPEND);
	else if(is_type(token, INPUT))
		input(mini, token);
	else if(is_type(token, PIPE))
		pipe = minipipe(mini)
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	int		status;

	token = next_run(mini->start, NOSKIP);
	if (is_types(token, "TAI"))
		token = mini->start->next;
	while(mini->flag == 0 && token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		redir_and_exc(mini, token);
	}
	
}

void	mini_init(t_mini *mini)
{
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	if (!mini->in || !mini->out)
		ft_panic("dup failed");
	mini->flag = 0;
	mini->ret = 0;
}

int	main(int ac, char **av, char **ev)
{
	t_mini	mini;

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
	}
}
