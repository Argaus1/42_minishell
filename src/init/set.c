/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:35:34 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/26 08:06:25 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	create_table_member(t_hashtable **env, \
	char *key, char *value, size_t index)
{
	t_member	*new;

	new = malloc(sizeof(t_member));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	*env[index] = new;
}

static void	fill_table(char **envp, t_hashtable *env, size_t size)
{
  	size_t	i;
  	size_t	index;

	index = 0;
	while (*envp)
	{
		i = 0;
		while (*envp[i] != '=')
			i++;
		if (*envp[i] == '=')
		{
			create_table_member(env, ft_substr(*envp, 0, i), \
				ft_substr(*envp, i + 1, ft_strlen(*envp) - i - 1), index);
			index++;
		}
		envp++;
	}
}

static void	create_table(t_hashtable **env, size_t size)
{
	*env = malloc(sizeof(t_hashtable));
	if (*env == NULL)
		return (NULL);
	(*env)->size = size;
	(*env)->member = ft_calloc(sizeof(t_member), size);
	if ((*env)->member == NULL)
	{
		free(*env);
		return (NULL);
	}
}

void	set_hashtable(char **envp, t_hashtable **env)
{
	size_t	size;

	size = ft_arrlen(envp);
	if (size == 0)
	{
		create_table(env, 1024);	//securiser
		return ;
	}
	create_table(env, size * 2);
	fill_table(envp, env, size * 2);
}

//print
//free
//delone
//find value
//add
//gt value
//print hash =/= print env
