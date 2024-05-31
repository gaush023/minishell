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

int  *make_in_sq_flag(char *line)
{
  int *str_flag;
  unsigned int i;
  int flag;

  i = 0;
  flag = 0;
	str_flag = ft_calloc(ft_strlen(line), sizeof(int));
  str_flag[ft_strlen(line)] = -3;
  while (line[i])
	{
    if(line[i] == '\'')
    {
      flag = 1;
      str_flag[i] = -2;
      i++;
      while (1)
      {
          if(line[i] == '\'' && line[i - 1] != '\\')
            break ;
          str_flag[i] = 0;
          i++; 
      }
    }
    if(line[i] == '\"')
    {
      flag = 1;
      str_flag[i] = -2;
      i++;
      while (1)
      {
        if(line[i] == '\"' && line[i- 1] != '\\')
            break ;
        str_flag[i] = 0;
        i++; 
      }
    }
    if(line[i] == ' ')
      str_flag[i] = -1;
    else if(flag == 1)
      str_flag[i] = -2;
    else
      str_flag[i] = 0;
    flag = 0;
    i++;
  }
  return (str_flag);
}

t_token *confirm_token_order(t_token *token)
{
    t_token *tmp;
    t_token *tmp2;  
    char *tmp_str;

    while(token->next != NULL)
    {
      if(token->qute_flag == 1)
      {
        tmp_str = ft_strjoin(token->content, token->next->content);
        token->content = ft_strdup(tmp_str);
        ft_free(tmp_str);
        printf("1\n");
        tmp = token->next;
        token->next = tmp->next; 
      }
      if(token->next != NULL)
        token = token->next;
    }
    
      while(token->prev != NULL)
        token = token->prev;

    if(token->type == HERE_DOC && token->qute_flag == 0)
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
    else if(token->type == HERE_DOC && token->qute_flag == 1)
    {
      ft_putstr_fd("minishell: command not found: <<\n", 2);
      free_token(token, 0);
      token = NULL;
    }
    return (token);
}

static t_token	*make_token(char *str, t_token *prev_token, int *quote_flag, int pos)
{
	t_token	*token;
  t_token *tmp;
  int i;

	token = ft_calloc(1, sizeof(t_token));
  token->prev = prev_token;
  if(quote_flag[pos] == -2)
  {  
    i = pos;
    if(quote_flag[pos + 1] && quote_flag[pos + 1] == -2)
      token->qute_flag = 1;
    else
      token->qute_flag = 0;
  }
  else 
    token->qute_flag = 0;
  token->content = ft_strdup(str);
	token->next = NULL;
	return (token);
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
  while(line[i] == ' ' && line[i] != '\0')
    i++;
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
		while (str_flag[i] == -1 || str_flag[i] == -2)
      i++;
    if (str_flag[i] == 0)
		{
			k = i;
			while (str_flag[i] == 0)
				i++;
			tmp_str = ft_calloc(i - k + 1, sizeof(char));
      ft_memcpy(tmp_str, &line[k], i - k);
			token = make_token(tmp_str, tmp_token, str_flag, i);
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
  token =  confirm_token_order(token);
  mini->start = token;
}

