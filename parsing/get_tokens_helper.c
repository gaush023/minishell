/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:07:22 by etakaham          #+#    #+#             */
/*   Updated: 2024/07/02 19:03:09 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_token_loops_helper(t_args *a);

void	set_type(t_token *token)
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

void	covert_blank_char(t_args *a)
{
	int	counter;
	int	pos;

	pos = 0;
	counter = 0;
	while (a->i != pos)
	{
		if (a->flag[pos] == -2)
			counter++;
		pos++;
	}
	if (counter % 2 != 0)
		return ;
	a->token = make_token("\0", a->tmp_t, a->flag, a->mini);
	a->tmp_t = a->token;
}

t_token	*get_token_loops(char *line, int *str_flag, t_mini *mini)
{
	t_args	tmp_args;
	int		i;

	tmp_args.l = line;
	tmp_args.flag = str_flag;
	tmp_args.mini = mini;
	tmp_args.token = NULL;
	tmp_args.tmp_t = NULL;
	tmp_args.i = 1;
	while (line[tmp_args.i])
	{
		while (str_flag[tmp_args.i] == -1 || str_flag[tmp_args.i] == -2)
		{
			if (str_flag[tmp_args.i + 1] == -2)
				covert_blank_char(&tmp_args);
			tmp_args.i++;
		}
		if (str_flag[tmp_args.i] == 0)
		{
			get_token_loops_helper(&tmp_args);
		}
	}
	i = 0;
	while (str_flag[i] != -3)
	{
		printf("str_flag[%d]: %d\n", i, str_flag[i]);
		i++;
	}
	return (tmp_args.token);
}
