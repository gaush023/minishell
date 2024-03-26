/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expasions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:39:43 by sagemura          #+#    #+#             */
/*   Updated: 2024/03/26 00:17:39 by sagemura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ret_size(int ret)
{
    char *tmp;
    int size;

    tmp = ft_itoa(ret);
    size = ft_strlen(tmp);
    if (tmp)
        free(tmp);
    return(size);
}

int get_var_len(const char *arg, int pos, t_env *env, int ret)
{
    char var_name[BUFF_SIZE];
    char *var_value;
    int i;

    i = 0;
    if(arg[pos] == '?')
        return(ret_size(ret));
    if(ft_isdigit(arg[pos]))
        return(0);
    while(arg[pos] && )
        
}

int malloc4expassion(char *arg, t_env *env, int ret)
{
    int i;
    int size;

    i = -1;
    size = 0;
    while (arg[++i])
    {
        if(arg[i] == EXPANSION)
        {
            i++;
            if((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
                size++;
            else
                size += get_var_len(arg, i, env, ret);
        }
        size++;
    }
    return (size);
}

char *expasions(char *arg, t_env *env, int ret)
{
    t_env ex;
    int len;
    
    len = malloc4expasion(arg, env, ret);
            
    
}