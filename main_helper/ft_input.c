/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuga <shuga@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:23:18 by sagemura          #+#    #+#             */
/*   Updated: 2024/07/30 16:35:56 by shuga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static bool is_echo(t_token *token)
{
    t_token *tmp;   

    return (false);
    tmp = token;
    while (tmp->type != CMD)
        tmp = tmp->prev;

    if (tmp->prev && ft_strncmp(tmp->prev->content, "echo", 5) == 0)
            return (true);
    return (false);
}



void	input(t_mini *mini, t_token *token)
{
	ft_close(mini->fdin);
	mini->fdin = open(token->content, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
        if(mini->is_printable == 0)
        {
		    ft_putstr_fd("minishell: ", STDERR);
            ft_putstr_fd(token->content, STDERR); 
		    ft_putstr_fd(" :No such file or directory\n", STDERR); 
            mini->is_printable = 1;
        }
        mini->ret = 1;
		mini->no_exec = 1;
        if(is_echo(token))
            mini->ret = 2;  
        return ;
	}
	dup2(mini->fdin, STDIN);
}
