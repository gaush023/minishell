#include "../includes/minishell.h"

void	ft_skip_space(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
}

int	ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
			&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

int	count_next(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	j = 0;
	count = 0;
	c = ' ';
	while ((line[*i + j] && line[*i + j] != ' ') || c != ' ')
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}

//見直す必要があり。
//echo "hello world" > file.txt で最後のトークンをコマンドして捉えているため。
void	type_token(t_token *token, int sep)
{
	if (ft_strcmp(token->content, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->content, ";") == 0 && sep == 0)
		token->type = SEMICOLON;
	else if (ft_strcmp(token->content, "<") == 0 && sep == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->content, "|") == 0 && sep == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->content, ">") == 0 && sep == 0)
		token->type = REDIR;
	else if (ft_strcmp(token->content, ">>") == 0 && sep == 0)
		token->type = APPEND;
	else if (token->prev == NULL || token->prev->type == REDIR)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = malloc(sizeof(char) * count_next(line, i));
	if (!token->content)
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if ((c == ' ' && line[*i] == '\'') || line[*i] == '\"')
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->content[j++] = line[(*i)++];
		else
			token->content[j++] = line[(*i)++];
	}
	token->content[j] = '\0';
	return (token);
}

t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_token(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < REDIR)
		token = token->next;
	return (token);
}

int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_sep(token, NOSKIP);
		if (prev && is_type(prev, SEMICOLON) && is_type(prev->prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

void	squish_content(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->start;
	while (token)
	{
		prev = prev_sep(token, NOSKIP);
		if (is_type(token, ARG) && is_types(token, "RAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			if (prev)
				prev->next = prev->next;
			else
				token->next = mini->start;
			if (!prev)
				prev = token;
			prev->next->prev = token;
			if (mini->start->prev)
				mini->start = mini->start->prev;
			else
				mini->start = token;
		}
		token = token->next;
	}
}
