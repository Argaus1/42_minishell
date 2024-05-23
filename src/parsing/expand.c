/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:00:48 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/23 15:01:23 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_quotes(char **new)
{
	char	**tmp;
	char	*str;

	tmp = ft_split(*new, '\"');
	free(*new);
	*new = NULL;
	str = ft_strdup(tmp[0]);
	free_array_2d(tmp);
	tmp = NULL;
	*new = str;
}

char	*ft_superjoin(char **strs, char *sep)
{
	size_t	size;
	size_t	i;
	char	*str;

	size = ft_arrlen(strs);
	i = 0;
	if (sep)
		str = ft_calloc(sizeof(char), (ft_megalen(strs) + \
			ft_strlen(sep) * size + 1));
	else
		str = ft_calloc(sizeof(char), ft_megalen(strs) + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		ft_strlcat(str, (const char *)strs[i], ft_strlen(str) \
			+ ft_strlen(strs[i]) + 1);
		if (sep)
			ft_strlcat(str, (const char *)strs[i], ft_strlen(str) \
				+ ft_strlen(sep) + 1);
		i++;
	}
	if (size == 0)
		return (NULL);
	printf("%s\n", str);
	return (str);
}

char	*expand(char *str, t_list **env, size_t size)
{
	char	**exp;
	char	**to_exp;
	char	*final;
	char	*new;
	size_t	i;

	i = 0;
	final = NULL;
	new = ft_substr(str, 0, size - 1);
	if (str[0] == '\"')
		delete_quotes(&new);
	to_exp = ft_split(new, '$');
	free(new);
	exp = ft_calloc(sizeof(char *), ft_arrlen(to_exp) + 1);
	if (!exp)
		return (NULL);
	while (to_exp[i])
	{
		exp[i] = ft_strdup(env_find_key(to_exp[i], env));
		i++;
	}
	free_array_2d(to_exp);
	final = ft_superjoin(exp, NULL);
	printf("%s\n", final);
	free_array_2d(exp);
	return (final);
}
