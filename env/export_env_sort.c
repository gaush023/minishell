#include "../includes/minishell.h"


void	sort_env_list(t_env *head)
{
	int swapped;
	char *temp_value;
	t_env *ptr;
	t_env *lptr;

	if (head == NULL)
		return ;
	lptr = NULL;
	swapped = 0;
	ptr = head;
	while (ptr->next != lptr)
	{
		if (ft_strcmp(ptr->value, ptr->next->value) > 0)
		{
			temp_value = ptr->value;
			ptr->value = ptr->next->value;
			ptr->next->value = temp_value;
			swapped = 1;
		}
		ptr = ptr->next;
	}
	lptr = ptr;
	while (swapped)
	{
		swapped = 0;
		ptr = head;

		while (ptr->next != lptr)
		{
			if (ft_strcmp(ptr->value, ptr->next->value) > 0)
			{
				temp_value = ptr->value;
				ptr->value = ptr->next->value;
				ptr->next->value = temp_value;
				swapped = 1;
			}
			ptr = ptr->next;
		}
		lptr = ptr;
	}
}