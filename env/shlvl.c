#include "../includes/minishell.h"

int  get_shlvl_plus(t_env *env) 
{
	size_t i;
	int shell_lvl;	
	char *tmp;

	i = 0;
	while(env && env->next)
	{
		if (ft_strncmp(env->value, "SHLVL=", 5) == 0)
		{
			tmp = ft_strchr(env->value, '=') + 1;
			shell_lvl = ft_atoi(tmp) + 1;
		        free(env->value);
			env->value = ft_strjoin("SHLVL=", ft_itoa(shell_lvl));
			return(0);
		}
		env = env->next;
	}
	return(ft_panic("SHLVL not found"));
}

//void print_env(t_env *env)
//{
//	while(env)
	//{
		//printf("%s\n", env->value);
		//env = env->next;
	//}
//}
//
//
//int main(int argc, char **argv, char **ev)
//{
	//t_mini *mini;
//
	//(void)argc;
	//(void)argv;
	//env_init(mini, ev);	
	//get_shlvl_plus(mini->env);
	//print_env(mini->env);
	//return(0);
//}
//

