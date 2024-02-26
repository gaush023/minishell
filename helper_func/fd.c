#include "../includes/minishell.h"

void reset_fds(t_mini *mini)
{
  mini->fdin = -1;
  mini->fdout = -1;
  mini->pipein = -1;
  mini->pipeout = -1;
  mini->m_pid = -1;
}

