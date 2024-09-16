/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:33:28 by sagemura          #+#    #+#             */
/*   Updated: 2024/09/16 17:33:37 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cmp_strings(const void *a, const void *b)
{
	char	*str_a;
	char	*str_b;

	str_a = *(char **)a;
	str_b = *(char **)b;
	return (strcmp(str_a, str_b));
}

void	print_declarre(char **values, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(values[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	sort_env_list(t_env *head)
{
	unsigned int	count;
	t_env			*current;
	char			**values;
	unsigned int	i;

	current = head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	values = (char **)malloc(sizeof(char *) * count);
	if (!values)
		return ;
	current = head;
	i = 0;
	while (current)
	{
		values[i++] = current->value;
		current = current->next;
	}
	qsort(values, count, sizeof(char *), cmp_strings);
	print_declarre(values, count);
	free(values);
}
