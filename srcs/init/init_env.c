# include "../../includes/minishell.h"

int	init_env(char **ev, t_env **env_data)
{
	t_env			*env;
	t_env			*new;
	unsigned int	i;

	env = ft_calloc(1, sizeof(t_env));
	env->value = ft_strdup(ev[0]);
	env->prev = NULL;
	env->next = NULL;
	*env_data = env;
	i = 1;
	while (ev && ev[0] && ev[i])
	{
		new = ft_calloc(1, sizeof(t_env));
		new->value = ft_strdup(ev[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
