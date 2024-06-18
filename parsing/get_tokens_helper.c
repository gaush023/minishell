/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:07:22 by etakaham          #+#    #+#             */
/*   Updated: 2024/06/18 02:20:52 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	t_token	*token;
	t_token	*tmp_token;
	int		i;
	int		k;
	char	*tmp_str;

	i = 0;
	tmp_token = NULL;
	token = NULL;

	while (line[i])
	{
		while (str_flag[i] == -1 || str_flag[i] == -2)
			i++;
		if (str_flag[i] == 0)
		{
			k = i;
			while (str_flag[i] == 0)
				i++;
			mini->pos = i;
			tmp_str = cutout_str(line, i, k, mini);
			if (tmp_str[0] == EXPANSION)
			{
				tmp_str++;
				if (ft_strcmp(tmp_str, "EMPTY") != 0)
				{
					tmp_str = cutout_str(line, i, k, mini);
					token = make_token(tmp_str, tmp_token, str_flag, mini);
					tmp_token = token;
				}
				else
					my_free(tmp_str, mini->m_node);
			}
			else
			{
				token = make_token(tmp_str, tmp_token, str_flag, mini);
				tmp_token = token;
			}
		}
	}
	return (token);
}
