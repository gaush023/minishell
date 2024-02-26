#include "../includes/minishell.h"

void mini_init(t_mini * mini)
{
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	if(!mini->in || !mini->out)
          ft_panic("dup failed");	
	mini->flag = 0;
	mini->ret = 0;
}

int main(int ac, char **av, char **ev)
{
	t_mini mini;

	(void)ac;
	(void)av;

	mini_init(&mini);
	reset_fds(&mini);
	env_init(&mini, ev);
	secret_env_init(&mini, ev);
	get_shlvl_plus(mini.env);
	while(mini.flag == 0)
	{
		
	}
}

