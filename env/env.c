#include "../includes/minishell.h"

int  env_init(t_mini *mini, char **evn_ar)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if(!(env = malloc(sizeof(t_env))))
		ft_panic(NULL, "Malloc failed at env_init", env_set);
	env->value = ft_strdup(evn_ar[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while(evn_ar && evn_ar[0] && evn_ar[i])
	{
		if(!(new = malloc(sizeof(t_env))))
			ft_panic(mini, "Malloc failed at env_init", env_set);
		if(!(new->value = ft_strdup(evn_ar[i])))
			ft_panic(mini, "Malloc failed at env_init(ft_strdup)", env_set);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int secret_env_init(t_mini *mini, char **env_ar)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return(0);
	env->value = ft_strdup(env_ar[0]);
	env->next = NULL;
	mini->secret_env = env;
	i = 1;
	while(env_ar && env_ar[0] && env_ar[i])
	{
		if(!(new = malloc(sizeof(t_env))))
			ft_panic(mini, "Malloc failed at secret_env_init", env_set);
		if(!(new->value = ft_strdup(env_ar[i])))
			ft_panic(mini, "Malloc failed at secret_env_init(ft_strdup)", env_set);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}


//void print_env(t_mini *mini)
//{
//	t_env *env;
//
//	env = mini->env;
//	while(env)
//	{
//		printf("%s\n", env->value);
//		env = env->next;
//	}
//}

// int main(int argc, char **argv, char **ev)
// {
//	t_mini mini;
//	int ret;
//
//	(void)argc;
//	(void)argv;
//	ret = env_init(&mini, ev);
//	print_env(&mini);
//	return (0);
//}
