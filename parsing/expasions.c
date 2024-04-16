/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expasions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sagemura <sagemura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:39:43 by sagemura          #+#    #+#             */
/*   Updated: 2024/04/16 19:47:22 by sagemura         ###   ########.fr       */
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


int is_env_char(char c)
{
    if(ft_isalnum(c) == 1 || c == '_')
        return(1);
    return(0);
}

void copy_env_name(char *env_name, char *env_value)
{
    int i;
    
    if(ft_strlen(env_value) > BUFF_SIZE)
        return(NULL);
    i = 0;
    while(env_name[i] != '=')
    {
        env_name[i] = env_value[i];
        i++;
    }
    env_name[i] = '\0';
    return(env_name);
}

int env_value_len(char *env)
{
    int i;  
    int size_name;
    
    size_name = 0;
    i = 0;
    while(env[i] && env[i] != '=')
       i++;
    i += 1;
    while(env[i])
    {
        size_name++;
        i++;
    }
    return(size_name);
}

char *copy_env_val(char *env)
{
    int i;
    int j;
    int size_allo;
    char *env_value;
    
    size_allo = env_value_len(env) + 1;
    if(!(env_value = (char *)malloc(sizeof(char) * size_allo)))
        return(NULL); // need to consider the case of malloc fail
    i = 0;
    while(env[i] && env[i] != '=')
        i++;
    j = 0;
    while(env[i])
    {
        env_value[j] = env[i];
        i++;
        j++;
    }
    env_value[j] = '\0';
    return(env_value);
}

char *get_env_value(char *var_name, t_env *env)
{
    char *env_name[BUFF_SIZE];
    char *env_value;
    
    env_value = ft_strdup("");
    // need to check if env_value is null
    while(env && env->value)
    {
        copy_env_name(env_name, env->value);
        if(ft_strcmp(env_name, var_name) == 0)
        {
            if(env_value)
                free(env_value);
            env_value = copy_env_val(env->value);
            return(env_value);
        }
        env = env->next;
    }
    return(env_value);
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
    while(arg[pos] &&  is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
    {
        var_name[i] = arg[pos];
        i++;
        pos++;
    }
    var_name[i] = '\0';
    var_value = get_env_value(var_name, env);
    i = ft_strlen(var_value);
    if(var_value)
        free(var_value);
    return(i);
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

char *get_var_val(char *arg, int pos, t_env *env, int ret)
{
    char var_name[BUFF_SIZE];
    char *var_value;
    int i;

    i = 0;
    if(arg[pos] == '?')
        return(ft_itoa(ret)); // need to consider the case of malloc fail
    if(ft_isdigit(arg[pos]))
        return(NULL);
    while(arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
    {
        var_name[i] = arg[pos];
        i++;
        pos++;
    }
    var_name[i] = '\0';
    var_value = get_env_value(var_name, env);
    return(var_value);
}

size_t var_cpy(char *dst, const  char *src, size_t size)
{
    size_t i;

    i = 0;
    while(src[i])
        dst[size++] = src[i++];
    return(i);
}

void insert_var(t_expasion *ex, char *arg, t_env *env, int ret)
{
    char *env_value;

    env_value = get_var_val(arg, ex->j, env, ret);   
    if(env_value)
        ex->i += var_cpy(ex->str, env_value, ex->i);
    if(env_value)
        free(env_value);
    if(arg[ex->j] == '?')
        ex->j++;
    if(ft_isdigit(arg[ex->j]) && arg[ex->j - 1] == '?')
    {
        while (is_env_char(arg[ex->j]) == 1)
            ex->j++;
    }
    else \
    {
        if(arg[ex->j] != EXPANSION)
            ex->j++;
    }
}

char *expasions(char *arg, t_env *env, int ret)
{
    t_expasion ex;
    int len;
    
    len = malloc4expasion(arg, env, ret);
    if(!(ex.str = (char *)malloc(sizeof(char) * (len + 1))))
        return(NULL); // need to consider the case of malloc fail　
    ex.i = 0;
    ex.j = 0;
    while(ex.i < len && arg[ex.j])
    {
        while(arg[ex.j] == EXPANSION)
        {
            ex.j++;
            if((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0) && arg[ex.j] != '?')
                    ex.str[ex.i] = EXPANSION;
            else
                insert_var(&ex, arg, env, ret);
        }
        ex.str[ex.i] = arg[ex.j];
        ex.i++;
        ex.j++;
    }
    ex.str[ex.i] = '\0';
    return(ex.str);
}