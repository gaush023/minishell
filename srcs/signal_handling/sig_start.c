# include "../../includes/minishell.h"

void	sig_start(int code)
{
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(" 🤯 "M_PROMPT, 2);
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_sig.sig_flag = 130;
	}
	g_sig.sigint = 1;
	return ;
	(void)code;
}
