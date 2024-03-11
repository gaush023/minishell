#include "../../includes/minishell.h"

void	type_contet(t_token *token, int sep)
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
	else if (token->prev == NULL || token->prev->type >= REDIR)
		token->type = CMD;
	else
		token->type = ARG;
}

void	ft_skip_space(const char *content, int *i)
{
	while ((content[*i] == ' ' || content[*i] == '\t')
	|| (content[*i] == '\r' || content[*i] == '\v' || content[*i] == '\f'))
		(*i)++;
}

int		ignore_sep(char *line, int i)
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

int		next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
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

t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	if (!(token = malloc(sizeof(t_token)))
	|| !(token->content = malloc(sizeof(char) * next_alloc(line, i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
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
		type_contet(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

void	test(t_mini *mini, char *line)
{
	mini->start = get_tokens(line);
	if(mini->start)
		printf("mini->start->content: %s\n", mini->start->content);
}

void print_tokens(t_token *token)
{
	while (token)
	{
		printf("token->content: %s\n", token->content);
		printf("token->type: %d\n", token->type);
		token = token->next;
	}
}

int	main(void)
{
	char *line =  "echo \"oh, Hello world!\" > test.txt";
	t_mini mini;
	test(&mini, line);
	print_tokens(mini.start);
	return (0);
}
