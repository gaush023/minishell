#include "../includes/minishell.h"

t_token *confirm_tokens(t_token *token)
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
        token->qute_flag = token->next->qute_flag;
        tmp = token->next;
        token->next = tmp->next; 
      }
      else if(token->next != NULL)
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

