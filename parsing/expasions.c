#include "../includes/minishell.h"

size_t	var_cpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i])
		dst[size++] = src[i++];
	printf("dst: %s\n", dst);
	return (i);
}

void	insert_var(t_expasion *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, env, ret);
	if (env_value)
		ex->i += var_cpy(ex->str, env_value, ex->i);
	ft_free(env_value);
	if (arg[ex->j] == '?')
		ex->j++;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != EXPANSION)
			ex->j++;
	}
}

char	*expasions(char *arg, t_env *env, int ret)
{
	t_expasion	ex;
	int			len;

	len = malloc4expassion(arg, env, ret);
	ex.str = (char *)malloc(sizeof(char) * (len + 1));
	if (ex.str == NULL)
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.str[ex.i++] = '$';
			else
				insert_var(&ex, arg, env, ret);
		}
		ex.str[ex.i] = arg[ex.j];
		ex.i++;
		ex.j++;
	}
	ex.str[ex.i] = '\0';
	return (ex.str);
}
