/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_startup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:48:27 by etakaham          #+#    #+#             */
/*   Updated: 2024/05/26 19:48:27 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_lib.h"

int	malloc_startup(t_node *head)
{
	head->ptr = NULL;
	head->is_free = true;
	head->next = NULL;
	head->size = 0;
	return (0);
}
