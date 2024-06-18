/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:07:22 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/18 20:56:43 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_token_loops_helper(t_args *a);

static void	set_type(t_token *token)
{
	if (ft_strcmp(token->content, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->content, ";") == 0)
		token->type = END;
	else if (ft_strcmp(token->content, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->content, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->content, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->content, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->content, "<<") == 0)
		token->type = HERE_DOC;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

char	*chek_prepareation(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (NULL);
	return (line);
}

t_token	*get_tokens_finish(t_token *token, t_mini *mini)
{
	if (token == NULL)
		return (NULL);
	while (token->prev != NULL)
	{
		set_type(token);
		token->prev->next = token;
		token = token->prev;
	}
	set_type(token);
	token = confirm_tokens(token, mini);
	return (token);
}

char	*cutout_str(char *line, unsigned int i, unsigned int k, t_mini *mini)
{
	char	*tmp_str;

	tmp_str = my_calloc(i - k + 1, sizeof(char), mini->m_node);
	ft_memcpy(tmp_str, &line[k], i - k);
	return (tmp_str);
}

t_token	*get_token_loops(char *line, int *str_flag, t_mini *mini)
{
	t_args	tmp_args;

	tmp_args.l = line;
	tmp_args.flag = str_flag;
	tmp_args.mini = mini;
	tmp_args.token = NULL;
	tmp_args.tmp_t = NULL;
	tmp_args.i = 0;
	while (line[tmp_args.i])
	{
		while (str_flag[tmp_args.i] == -1 || str_flag[tmp_args.i] == -2)
			tmp_args.i++;
		if (str_flag[tmp_args.i] == 0)
		{
			get_token_loops_helper(&tmp_args);
		}
	}
	return (tmp_args.token);
}
