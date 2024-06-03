#include "../includes/minishell.h"

int	ret_size(int ret)
{
	char	*tmp;
	int		size;

	tmp = ft_itoa(ret);
	size = ft_strlen(tmp);
	if (tmp)
		free(tmp);
	return (size);
}

int	is_env_char(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

char	*copy_env_name(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && i < BUFF_SIZE)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	env_value_len(char *env)
{
	int	i;
	int	size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char	*copy_env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	if (!(env_value = (char *)malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *var_name, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_value;

	env_value = ft_strdup("");
	while (env && env->value)
	{
		copy_env_name(env_name, env->value);
		if (ft_strcmp(env_name, var_name) == 0)
		{
			ft_free(env_value);
			env_value = copy_env_value(env->value);
			return (env_value);
		}
		env = env->next;
	}
	return (env_value);
}

int	get_var_len(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
		return (ret_size(ret));
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
		var_name[i++] = arg[pos++];
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	i = ft_strlen(var_value);
	ft_free(var_value);
	return (i);
}

char	*get_var_value(char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
		var_name[i++] = arg[pos++];
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}

int	malloc4expassion(char *arg, t_env *env, int ret)
{
	char	*env_value;
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
			{
				size++;
			}
			else
			{
				size += get_var_len(arg, i, env, ret);
			}
			if (ft_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_env_char(arg[i]) == 1)
					i++;
			}
			else
			{
				size--;
			}
		}
		size++;
	}
	return (size);
}
