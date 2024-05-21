#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>


void sig_int(int code) {
    (void)code;
    if (g_sig.pid != 0) {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    } 
    else 
    {
        if (g_sig.heredoc_flag == 1) {
            ft_putstr_fd("\n", STDERR_FILENO);
            ft_putstr_fd(M_PROMPT, STDERR_FILENO);
            g_sig.sigint = 1;
            return;
        }
        ft_putstr_fd("\n", STDERR_FILENO);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putstr_fd(nbr, STDERR);
		g_sig.sig_flag = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b \b\b", STDERR);
	ft_free(nbr);
}

void	ini_sig(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
  g_sig.heredoc_flag = 0;
}
