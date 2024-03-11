#include "includes/minishell.h"


int count_next(char *line, int *i)
{
	int count;
	int j;
	char c;

	j = 0;
	count = 0;
	c = ' ';
	while(line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if(c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if(c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else 
			j++;
		if(j > 0 && line[*i + j - 1] == '\\')
			count--;
	}
	return(j - count + 1);
}


t_token *next_token(char *line, int *i)
{
	t_token *token;
	int j;
	char c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	if(!token)
		return (NULL);
	token->content = malloc(sizeof(char) * count_next(line, i));
 	if(!token->content)
	    return (NULL);
        while(line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if(c == ' ' && (line[*i]) == '\'' || line[*i] == '\"')
			c = line[*i++];
		else if(c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if(line[*i] == '\\' && (*i)++)
			token->content[j++] = line[(*i)++];
		else
			token->content[j++] = line[(*i)++];
	}
	token->content[j] = '\0';
	return (token);
}

int main(void)
{
  char *test;
  t_token *prev;
  int i;

  i = 0;
  prev = NULL;
  test = "echo \"hello world\"";
  prev = next_token(test, &i);
  printf("%s\n", prev->content);
}

