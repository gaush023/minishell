#include "../includes/minishell.h"

int ft_panic(char *msg)
{
    perror(msg);
    exit(1);
}
