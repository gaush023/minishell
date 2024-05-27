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

t_token *confirm_token_order(t_token *token)
{
    t_token *tmp;
    t_token *tmp2;  

    if(token->type == HERE_DOC)
    {
      if(!token->next->next || token->next->next->type != ARG)
      {
        tmp = ft_calloc(1, sizeof(t_token));
        tmp->content = ft_strdup("cat");
        tmp->type = CMD;
        tmp->next = token;
        tmp->prev = NULL;
        token->prev = tmp;
        token = token->prev;
        return (token); 
      }    
      else if(token->next->next->type == ARG)
      { 
        tmp = NULL;
        tmp = token->next->next;
        tmp->type = CMD;
        tmp->prev = NULL;
        tmp2 = token->next->next->next;
        token->next->next = tmp2;  
        token->prev = tmp;
        tmp->next = token;
        tmp->prev = NULL;
        token = token->prev;
        return (token);
      }
    }
    return (token);
}

static t_token	*make_token(char *str, t_token *prev_token)
{
	t_token	*token;
  t_token *tmp;

	token = ft_calloc(1, sizeof(t_token));
  if(str[0] == '\\')
    str++; 
  token->prev = prev_token;
  token->content = ft_strdup(str);
	token->next = NULL;
	return (token);
}

static int is_all_space(char *line)
{
  unsigned int	i;
  char *tmp;

  i = 0;
  tmp = ft_strdup(line);
  while (tmp[i] != '\n')
  {
    if (tmp[i] != ' ') 
    {
      ft_free(tmp);
      return (0);
    }
    i++;
  }
  ft_free(tmp);
  return (1);

}

void	get_tokens(char *line, t_mini *mini)
{
	t_token			*token;
	t_token			*tmp_token;
	char			*tmp_str;
	unsigned int	i;
	unsigned int	k;
	int				*str_flag;
  int flag;

  i = 0;
  if((line[i] == '\\' || line[i] == ';' || line[i] == ':') && line[i + 1] == '\0')
  {
    mini->start = NULL;
    return ;
  }
  while (line[i] == ' ')
    i++;
	if (line[i] == '\0' )
	{
		mini->start = NULL;
		return ;
	}
	str_flag = make_in_sq_flag(line);
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
			ft_free(tmp_str);
			tmp_token = token;
		}
	}
	ft_free(str_flag);
	while (token->prev != NULL)
	{
	  set_type(token);
		token->prev->next = token;
    token = token->prev;
  }
	set_type(token);
  t_token *tmp;
  tmp = token;
  while (tmp)
  {
    printf("content: %s\n", tmp->content);
    printf("type: %d\n", tmp->type);
    tmp = tmp->next;
  }
  token =  confirm_token_order(token);
  tmp = token;
  while (tmp)
  {
    printf("content: %s\n", tmp->content);
    printf("type: %d\n", tmp->type);
    tmp = tmp->next;
  }
  mini->start = token;
}

