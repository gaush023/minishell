# include "../../includes/minishell.h"

int	get_shlvl_plus(t_env *env)
{
	int		shlvl;
	int		is_cmp;
	char	*tmp;

	while (env && env->next)
	{
		is_cmp = ft_strncmp(env->value, "SHLVL=", 5);
		if (is_cmp == 0)
		{
			tmp = ft_strchr(env->value, '=') + 1;
			shlvl = ft_atoi(tmp) + 1;
			free(env->value);
			env->value = ft_strjoin("SHLVL=", ft_itoa(shlvl));
			return (0);
		}
		env = env->next;
	}
	return (0);
}
