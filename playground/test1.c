#include <unistd.h>
#define STDERR 2

typedef struct t_mini
{
	int ret;
}				t_mini;

void ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

int main(void)
{
	t_mini mini;

	mini.ret = 1;
	mini.ret ? ft_putstr_fd("🤬 ", STDERR) : ft_putstr_fd("😎 ", STDERR);
	ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
	write(1, "\n", 1);
	mini.ret = 0;
	mini.ret ? ft_putstr_fd("🤬 ", STDERR) : ft_putstr_fd("😎 ", STDERR);
	ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
	return (0);
}

