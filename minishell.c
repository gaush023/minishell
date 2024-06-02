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



void	redir(t_mini *mini, t_token *token, int type)
{
  printf("Start of redir\n");
  ft_close(mini->fdout);
	if (type == TRUNC)
		mini->fdout = open(token->content, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRWXU);
	else
		mini->fdout = open(token->content, O_WRONLY | O_CREAT | O_APPEND,
				S_IRWXU);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->content, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->ret = 500;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

void	input(t_mini *mini, t_token *token)
{
	ft_close(mini->fdin);
	mini->fdin = open(token->content, O_RDONLY, S_IRUSR);
	if (mini->fdin < 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->content, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		mini->ret = 200;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}

int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
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

void here_doc(t_mini *mini, t_token *token)
{
	char *delimiter;
	char *line;

  mini->charge = 0;
  g_sig.heredoc_flag = 1;
  delimiter = token->content;
	mini->heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(mini->heredoc_fd == -1)
	    return ;
	while(1)
	{
    signal(SIGINT, sig_int);
    printf("here_doc:0\n");
    if (g_sig.sigint == 1)
    {
      printf("止まります\n");
      mini->charge = 1;
      g_sig.heredoc_flag = 0;
      break ;
    }
    printf("here_doc:1\n");
    printf("g_sig.sigint: %d\n", g_sig.sigint);
    printf("g_sig.heredoc_flag: %d\n", g_sig.heredoc_flag);
    line = readline("heredoc>  \b");
    printf("here_doc:2\n");
    if (g_sig.sigint == 1)
    {
      printf("line: %s\n", line); 
      printf("tmp->content: %s\n", token->prev->prev->content);
      token->prev->prev->content = line;
      mini->charge = 1;
      g_sig.heredoc_flag = 0;
      break ;
    }
    printf("here_doc:3\n");
  	if (!line || ft_strcmp(line, delimiter) == 0 )
		{
      if(!line)
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
	if(g_sig.sigint != 1)
    mini->heredoc_fd = open("/tmp/heredoc_tmp", O_RDONLY);
  else 
    mini->heredoc_fd = open("/dev/null" , O_RDONLY);
  if (mini->heredoc_fd == -1)
		return ;
  dup2(mini->heredoc_fd, STDIN);
	ft_close(mini->heredoc_fd);
  if(g_sig.sigint != 1)
    g_sig.heredoc_flag = 0;
  else
    g_sig.heredoc_flag = 1;
  if(g_sig.sigint != 1)
    mini->charge = 1;
}


t_token *prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

  prev = prev_sep(token, SKIP);
	next = next_sep(token, SKIP);
	pipe = 0;

  t_token *tmp = token;
  while(tmp)
  {
    printf("redir_and_exec: tmp->content: %s\n", tmp->content);
    tmp = tmp->next;
  }
  if (is_type(prev, TRUNC))
  {
	  printf("redir_and_exec: is_type(prev, TRUNC)\n");
    redir(mini, token, TRUNC);
  }
	else if (is_type(prev, APPEND))
  {
    printf("redir_and_exec: is_type(token, APPEND)\n");
		redir(mini, token, APPEND);
  }
	else if (is_type(prev, INPUT))
  {
    printf("redir_and_exec: is_type(prev, INPUT)\n");
	  input(mini, token);
  }
  else if (is_type(prev, PIPE))
  {
    printf("redir_and_exec: is_type(prev, PIPE)\n");
    pipe = minipipe(mini);
  }
	else if(is_type(prev, HERE_DOC))
  {
    printf("redir_and_exec: is_type(prev, HERE_DOC)\n");
    here_doc(mini, token);
  }
	if (next && is_type(next, END) == 0 && pipe != 1)
  {
    printf("redir_and_exec: is_type(next, END) == 0 && pipe != 1\n");
    redir_and_exec(mini, next->next);
  }
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev) && pipe != 1
		&& mini->no_exec == 0 )
  {
    printf("redir_and_exec: is_type(prev, END) || is_type(prev, PIPE) || !prev\n");
    exec_cmd(mini, token);
  }
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	int		status;
  
	token = next_run(mini->start, NOSKIP); 
  if (is_types(token, "TAIH"))
		token = mini->start->next;
  printf("token->content minishell: %s\n", token->content);
  while (mini->flag == 0 && token)
	{
    printf("minishell start\n");
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
    redir_and_exec(mini, token);
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (mini->last == 0)
			mini->ret = status;
		if (mini->parent == 0)
		{
			free_token(mini->start, mini->flag);
			exit(mini->ret);
		}
		mini->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }

void	mini_init(t_mini *mini)
{
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	if (!mini->in || !mini->out)
		ft_panic(NULL, "dup", 1);
	mini->flag = 0;
	mini->ret = 0;
  mini->no_exec = 0;
}


int	main(int ac, char **av, char **ev)
{
	t_mini	mini;

	(void)ac;
	(void)av;

	mini_init(&mini);
	env_init(&mini, ev);
	secret_env_init(&mini, ev);
	get_shlvl_plus(mini.env);
	while (mini.flag == 0)
	{
		ini_sig();
    parse(&mini);
    if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
    free_token(mini.start, mini.flag);
  }
	free_all(&mini, 0);
	return (mini.ret);
	// system("leaks -q minishell");
}

