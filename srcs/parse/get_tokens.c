# include "../../includes/minishell.h"

static int	ignore_sep(char *line, int i)
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

static int	count_next(char *line, int *i)
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

static void	set_token_type(t_token *token, int sep)
{
	if (ft_strcmp(token->com, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->com, ";") == 0 && sep == 0)
		token->type = END;
	else if (ft_strcmp(token->com, "<") == 0 && sep == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->com, "|") == 0 && sep == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->com, ">") == 0 && sep == 0)
		token->type = REDIR;
	else if (ft_strcmp(token->com, ">>") == 0 && sep == 0)
		token->type = APPEND;
	else if (token->prev == NULL || token->prev->type == REDIR)
		token->type = CMD;
	else
		token->type = ARG;
}

static t_token	*next_token(char *line, int *i, t_data *data)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = ft_calloc(1, sizeof(t_token));
	token->com = ft_calloc(count_next(line, i), sizeof(char));
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
			token->com[j++] = line[(*i)++];
		else
			token->com[j++] = line[(*i)++];
	}
	token->com[j] = '\0';
	return (token);
	(void)data;
}

int	get_tokens(char *line, t_data *data)
{
	t_token				*prev;
	t_token				*next;
	int					i;
	int					sep;

	prev = NULL;
	next = NULL;
	sep = 0;
	i = 0;
	ft_skip_space(line, &i);

	//=====確認用のプロンプト======
	printf("================orignal line================\n");
	printf("%s\n", line);
	printf("strlen is %zu\n\n", ft_strlen(line));
	//=============================

	printf("======check char======\n");
	while (line[i])
	{
		printf("check \'%c\'    ", line[i]);
		sep = ignore_sep(line, i);
		printf("sep is %d\n", sep);
		next = next_token(line, &i, data);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		set_token_type(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;

	//=====確認用のプロンプト======
	printf("================last tokens================\n");
	while (next->next != NULL)
	{
		if (next->type == EMPTY)
			printf("type is EMPTY\n");
		else if (next->type == END)
			printf("type is END\n");
		else if (next->type == INPUT)
			printf("type is INPUT\n");
		else if (next->type == PIPE)
			printf("type is PIPE\n");
		else if (next->type == REDIR)
			printf("type is REDIR\n");
		else if (next->type == APPEND)
			printf("type is APPEND\n");
		else if (next->type == CMD)
		{
			printf("type is CMD\n");
			printf("cmd is {%s}\n", next->com);
		}
		else if (next->type == ARG)
			printf("type is ARG\n");
		next = next->next;
	}
	//=============================

	return (0);
	(void)data;
}





















/*
	@return	0 : 通常終了
			1 : ''が閉じられていなかったため終
*/
int	__get_tokens(char *line)
{
	t_token			*token1;
	char			**tmp;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	token1 = ft_calloc(1, sizeof(t_token));
	tmp = ft_calloc(15, sizeof(char*));

	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		printf("=========this is %c========\n", line[i]);
		if (line[i] == '\'')
		{
			j = 1;
			while (line[i + j])
			{
				printf("=========this is %c========\n", line[i]);
				printf("this is sig\ti is %u :j is %u:char is %c :k is %u\n", i, j, line[i+j], k);
				if (line[i + j] == '\'')
				{
					tmp[k] = ft_calloc(j, sizeof(char));
					ft_memcpy(tmp[k], &line[i + 1], j - 1);
					i += (j);
					k++;
					break ;
				}
				j++;
			}
		}
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			i--;
			j = 1;
			while (line[i + j])
			{
				printf("=========this is %c========\n", line[i]);
				printf("this is spa\ti is %u :j is %u:char is %c :k is %u\n", i, j, line[i+j], k);
				if (line[i + j] == '\'')
				{
					tmp[k] = ft_calloc(j, sizeof(char));
					ft_memcpy(tmp[k], &line[i + 1], j - 1);
					i += j;
					i--;
					break;
				}
				else if (line[i + j] == ' ')
				{
					tmp[k] = ft_calloc(j, sizeof(char));
					ft_memcpy(tmp[k], &line[i + 1], j - 1);
					i += j;
					k++;
					break;
				}
				j++;
			}
		}
		i++;
	}
	tmp[k] = NULL;
	i = 0;
	while (tmp[i] != NULL)
	{
		printf("%u : %s\n", i, tmp[i]);
		i++;
	}
	return (0);
}




















