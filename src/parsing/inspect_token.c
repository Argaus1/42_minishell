/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:05:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/05/28 13:33:45 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static size_t	isolate_not_exp(char *str, t_bool exp, t_exp **exp_status, \
		t_list **splitted_token)
{
	size_t	i;
	t_list	*new;

	i = 0;
	printf("str[0] dans isoate not exp: %c\n", str[i]);
	while (str[i] && exp == false && (str[i] != '$' || \
		((*exp_status)->esc_status->is_quoted == true && \
		(*exp_status)->esc_status->is_simplequote == true)))
	{
		i++;
		if (str[i])
			exp = check_expansion(exp_status, &str[i]);
		printf("str[i] = %c\n", str[i]);
	}
	if (i != 0)
	{
		new = ft_lstnew(ft_substr(str, 0, i));
		ft_lstadd_back(splitted_token, new);
	}
	if (str[i] == '\"' && exp == true)
	{
		i -= 1;
		(*exp_status)->is_exp_quo = false;
		(*exp_status)->esc_status->is_quoted = false;
	}
	return (i);
}

static size_t	isolate_exp(char *str, t_list **env, \
		t_exp **exp_status, t_list **splitted_token)
{
	t_list	*new;
	t_bool	exp;
	size_t	i;

	i = 0;
	exp = true;
	printf("isolateexp\n");
	while (str[i] && exp == true)
	{
		i++;
		printf("str[i] = %c\n", str[i]);
		if ((str[i] && i == 1 && (!ft_isalpha(str[i]) && (str[i] != '_' && str[i] != '$'))))
		//	|| (str[i - 1] == '$' && (str[i] == '\'' || str[i] == '"') && (*exp_status)->esc_status->is_quoted == true))
		{
			printf("jesors\n");
			if ((*exp_status)->esc_status->is_quoted == true && str[i - 1] == '$' && (str[i] == '\'' || str[i] == '"'))
				i = 0;
			(*exp_status)->is_exp_sim = false;
			break ;
		}
		else if (str[i] && !ft_isalnum(str[i]) && str[i] != '_' && (*exp_status)->esc_status->is_quoted == false)
		{
			(*exp_status)->is_exp_sim = false;
			i--;
			printf("jusorsB\n");
			break ;}
		exp = check_expansion(exp_status, &str[i]);
		if (exp == false)
			i--;
		
	}
	if (i != 0)
	{
		new = ft_lstnew(expand(str, env, i + 2, (*exp_status)->esc_status));
		ft_lstadd_back(splitted_token, new);
	}
	return (i);
}

void	inspect_token(char **str, t_list **env)
{
	size_t	i;
	t_list	*splitted_token;
	t_bool	exp;
	t_exp	*exp_status;

	i = 0;
	splitted_token = NULL;
	init_tracker(&exp_status);
	while (i < ft_strlen(str[0]) && str[0][i] != 0)
	{
		exp = check_expansion(&exp_status, &str[0][i]);
		if (exp == false)
			i += isolate_not_exp(&str[0][i], exp, &exp_status, &splitted_token);
		else if (str[0][i] && str[0][i] != '?')
			i += isolate_exp(&str[0][i], env, &exp_status, &splitted_token);
		else
		{
			ft_lstadd_back(&splitted_token, ft_lstnew(ft_itoa(g_status)));
			//i += 1;
			exp_status->is_exp_sim = false;
		}
		i++;
	}
	if (splitted_token)
		join_after_expansion(&str[0], &splitted_token);
	//printf("%s\n", *str);
	free(exp_status->esc_status);	
	free(exp_status);	
	ft_lstclear(&splitted_token, free);
}
