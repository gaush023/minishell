/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:14:48 by sagemura          #+#    #+#             */
/*   Updated: 2023/07/10 09:15:23 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int argument)
{
	return (((argument >= 'a') && (argument <= 'z')) || ((argument >= '0')
			&& (argument <= '9')) || ((argument >= 'A') && (argument <= 'Z')));
}
