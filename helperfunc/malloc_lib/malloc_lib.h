/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lib.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etakaham <etakaham@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:48:21 by etakaham          #+#    #+#             */
/*   Updated: 2024/05/26 19:48:21 by etakaham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_LIB_H
# define MALLOC_LIB_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_node
{
	void			*ptr;
	bool			is_free;
	size_t			size;
	struct s_node	*next;
}			t_node;

void	*ft_malloc(size_t size, t_node *node);
void	*ft_calloc(size_t count, size_t size, t_node *node);
void	*ft_realloc(void *ptr, size_t size, t_node *node);
int		malloc_startup(t_node *head);
int		ft_free(void *ptr, t_node *node);
int		malloc_end(t_node *node);
void	ft_exit(int status, t_node *node);
#endif
