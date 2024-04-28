# include "../../includes/minishell.h"

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putstr_fd(nbr, 2);
		g_sig.sig_flag = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b \b\b", 2);
}
