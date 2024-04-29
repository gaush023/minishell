# include "../../includes/minishell.h"

static void	set_type(t_token *token)
{
	if (ft_strcmp(token->com, "") == 0)
	{
		token->type = EMPTY;
		printf("this is enp? : %s\n", token->com);
	}
	else if (ft_strcmp(token->com, ";") == 0)
		token->type = END;
	else if (ft_strcmp(token->com, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->com, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->com, ">") == 0)
		token->type = REDIR;
	else if (ft_strcmp(token->com, ">>") == 0)
		token->type = APPEND;
	else if (token->prev == NULL || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}


static int	*make_in_sq_flag(char *line)
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
		if (line[i] == '\'')
		{
			if (is_in_sq)
				is_in_sq = false;
			else
				is_in_sq = true;
			str_flag[i] = -1;
		}
		else if (line[i] == ' ' && !is_in_sq)
		{
			str_flag[i] = -1;
		}
		else
		{
			str_flag[i] = 0;
		}
		i++;
	}
	return (str_flag);
}

static t_token	*make_token(char *text, t_token *prev)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(token));
	token->com = ft_strdup(text);
	token->prev = prev;
	token->next = NULL;
	return (token);
}

int	get_tokens(char *line, t_data *data)
{
	t_token			*token;
	t_token			*tmp_token;
	char			*tmp;
	unsigned int	i;
	unsigned int	k;
	int				*str_flag;

	str_flag = make_in_sq_flag(line);
	tmp_token = ft_calloc(1, sizeof(t_token));
	token = ft_calloc(1, sizeof(t_token));
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
			tmp = ft_calloc(i-k+1, sizeof(char));
			ft_memcpy(tmp, &line[k], i-k);
			token = make_token(tmp, tmp_token);
			tmp_token = token;
		}
	}
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
	{
		token = token->prev;
	}
	data->token = token;
	return (0);
}
