#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

# include <stdbool.h>

int		ft_error(void);
void	ft_skip_space(char *line, int *i);
void	ft_free(void *ptr);
bool	ft_equals(const char *s1, const char *s2);

#endif
