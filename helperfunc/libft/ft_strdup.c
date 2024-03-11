#include "../../includes/minishell.h"

char *ft_strdup(const char *s)
{
	char *new;
	size_t len;
	size_t i;

	len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

