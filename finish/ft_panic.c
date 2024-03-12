#include "../includes/minishell.h"

void ft_panic(t_mini *mini, char *str,  enum e_err err_type)
{
    write(2, "Error: ", 7);
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    if(mini != NULL)
        free_all(mini, err_type);
    exit(1);
}