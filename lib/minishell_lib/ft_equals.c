# include "./minishell_lib.h"
# include <stdbool.h>
# include <stdlib.h>

bool	ft_equals(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == '\n')
			return (true);
		else if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s1[i] == '\n')
		return (true);
	else if (s1[i] != s2[i])
		return (false);
	return (true);
}
