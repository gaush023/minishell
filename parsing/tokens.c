#include "../includes/minishell.h"

static void	set_type(t_token *token)
{
	if (ft_strcmp(token->content, "") == 0)
	{
		token->type = EMPTY;
		printf("this is enp?: %s\n", token->content);
	}
	else if (ft_strcmp(token->content, ";") == 0)
		token->type = END;
	else if (ft_strcmp(token->content, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->content, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->content, ">") == 0)
		token->type = REDIR;
	else if (ft_strcmp(token->content, ">>") == 0)
		token->type = APPEND;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

static t_token	*make_token(char *str, t_token *prev)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->content = ft_strdup(str);
	token->prev = prev;
	token->next = NULL;
	return (token);
}

int	*make_in_sq_flag(char *line)
{
	int				*str_flag;
	bool			is_in_sq;
	unsigned int	i;

	str_flag = ft_calloc(ft_strlen(line), sizeof(int));
	str_flag[ft_strlen(line)] = -2;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
			i = i + 2;
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (is_in_sq)
				is_in_sq = false;
			else
				is_in_sq = true;
			str_flag[i] = -1;
		}
		else if (line[i] == ' ' && !is_in_sq)
			str_flag[i] = -1;
		else
			str_flag[i] = 0;
		i++;
	}
	return (str_flag);
}

void get_tokens(char *line, t_mini *mini)
{
	t_token			*token;
	t_token			*tmp_token;
	char			*tmp_str;
	unsigned int	i;
	unsigned int	k;
	int				*str_flag;

	str_flag = make_in_sq_flag(line);
	tmp_token = ft_calloc(1, sizeof(t_token));
	tmp_token = NULL;
	i = 0;
	k = 0;
	while (line[i])
	{
		while (str_flag[i] == -1)
			i++;
		if (str_flag[i] == 0)
		{
			k = i;
			while (str_flag[i] == 0)
				i++;
			tmp_str = ft_calloc(i - k + 1, sizeof(char));
			ft_memcpy(tmp_str, &line[k], i - k);
			token = make_token(tmp_str, tmp_token);
			tmp_token = token;
		}
	}
	ft_free(str_flag);
	while (token->prev)
	{
		token->prev->next = token;
		token = token->prev;
	}
	while (token->next)
	{
		set_type(token);
		token = token->next;
	}
	set_type(token);
	while (token->prev)
		token = token->prev;
	mini->start = token;
}

// void	ft_skip_space(char *line, int *i)
// {
// 	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
// 		(*i)++;
// }

// int	ignore_sep(char *line, int i)
// {
// 	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
// 		return (1);
// 	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
// 		return (1);
// 	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
// 		return (1);
// 	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
// 		&& line[i + 2] && line[i + 2] == '>')
// 		return (1);
// 	return (0);
// }

// int	count_next(char *line, int *i)
// {
// 	int		count;
// 	int		j;
// 	char	c;

// 	j = 0;
// 	count = 0;
// 	c = ' ';
// 	while ((line[*i + j] && line[*i + j] != ' ') || c != ' ')
// 	{
// 		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
// 			c = line[*i + j++];
// 		else if (c != ' ' && line[*i + j] == c)
// 		{
// 			count += 2;
// 			c = ' ';
// 			j++;
// 		}
// 		else
// 			j++;
// 		if (line[*i + j - 1] == '\\')
// 			count--;
// 	}
// 	return (j - count + 1);
// }

// void	type_token(t_token *token, int sep)
// {
// 	if (ft_strcmp(token->content, "") == 0)
// 		token->type = EMPTY;
// 	else if (ft_strcmp(token->content, ";") == 0 && sep == 0)
// 		token->type = END;
// 	else if (ft_strcmp(token->content, "<") == 0 && sep == 0)
// 		token->type = INPUT;
// 	else if (ft_strcmp(token->content, "|") == 0 && sep == 0)
// 		token->type = PIPE;
// 	else if (ft_strcmp(token->content, ">") == 0 && sep == 0)
// 		token->type = TRUNC;
// 	else if (ft_strcmp(token->content, ">>") == 0 && sep == 0)
// 		token->type = APPEND;
// 	else if (token->prev == NULL || token->prev->type == TRUNC)
// 		token->type = CMD;
// 	else
// 		token->type = ARG;
// }

// t_token	*next_token(char *line, int *i, t_mini *mini)
// {
// 	t_token	*token;
// 	int		j;
// 	char	c;

// 	j = 0;
// 	c = ' ';
// 	if (!(token = malloc(sizeof(t_token))))
// 		ft_panic(mini, "Malloc failed at next_token: token", err_token);
// 	if (!(token->content = malloc(sizeof(char) * count_next(line, i))))
// 	{
// 		free(token);
// 		free(line);
// 		ft_panic(mini, "Malloc failed at next_token: token->content",
// 			err_token);
// 	}
// 	while (line[*i] && (line[*i] != ' ' || c != ' '))
// 	{
// 		if ((c == ' ' && line[*i] == '\'') || line[*i] == '\"')
// 			c = line[(*i)++];
// 		else if (c != ' ' && line[*i] == c)
// 		{
// 			c = ' ';
// 			(*i)++;
// 		}
// 		else if (line[*i] == '\\' && (*i)++)
// 			token->content[j++] = line[(*i)++];
// 		else
// 			token->content[j++] = line[(*i)++];
// 	}
// 	token->content[j] = '\0';
// 	return (token);
// }

// t_token	*get_tokens(char *line, t_mini *mimi)
// {
// 	t_token	*prev;
// 	t_token	*next;
// 	int		i;
// 	int		sep;

// 	prev = NULL;
// 	next = NULL;
// 	i = 0;
// 	ft_skip_space(line, &i);
// 	while (line[i])
// 	{
// 		sep = ignore_sep(line, i);
// 		next = next_token(line, &i, mimi);
// 		next->prev = prev;
// 		if (prev)
// 			prev->next = next;
// 		prev = next;
// 		type_token(next, sep);
// 		ft_skip_space(line, &i);
// 	}
// 	if (next)
// 		next->next = NULL;
// 	while (next && next->prev)
// 		next = next->prev;
// 	return (next);
// }

// t_token	*prev_sep(t_token *token, int skip)
// {
// 	if (token && skip)
// 		token = token->prev;
// 	while (token && token->type < TRUNC)
// 		token = token->prev;
// 	return (token);
// }

// int	is_last_valid_arg(t_token *token)
// {
// 	t_token	*prev;

// 	if (!token || is_type(token, CMD) || is_type(token, ARG))
// 	{
// 		prev = prev_sep(token, NOSKIP);
// 		if (prev && is_type(prev, END) && is_type(prev->prev, PIPE))
// 			return (1);
// 		return (0);
// 	}
// 	else
// 		return (0);
// }

// void	squish_content(t_mini *mini)
// {
// 	t_token	*token;
// 	t_token	*prev;

// 	token = mini->start;
// 	while (token)
// 	{
// 		prev = prev_sep(token, NOSKIP);
// 		if (is_type(token, ARG) && is_types(token, "TAI"))
// 		{
// 			while (is_last_valid_arg(prev) == 0)
// 				prev = prev->prev;
// 			token->prev->next = token->next;
// 			if (token->next)
// 				token->next->prev = token->prev;
// 			token->prev = prev;
// 			if (prev)
// 				token->next = prev->next;
// 			else
// 				token->next = mini->start;
// 			if (prev)
// 				prev = prev;
// 			else
// 				prev = token;
// 			prev->next->prev = token;
// 			if (mini->start->prev)
// 				prev->next = prev->next;
// 			else
// 				prev->next = token;
// 			if (mini->start->prev)
// 				mini->start = mini->start->prev;
// 			else
// 				mini->start = mini->start;
// 		}
// 		token = token->next;
// 	}
// }
