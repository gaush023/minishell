# include "../../includes/minishell.h"

int	init_sig()
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.sig_flag = 0;
	return (0);
}
