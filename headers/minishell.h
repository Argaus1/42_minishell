/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:11:16 by aboulore          #+#    #+#             */
/*   Updated: 2024/04/12 16:12:56 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include "libft.h"
# include "keys.h"

typedef enum e_bool { false, true }	t_bool;

typedef struct s_esc
{
	t_bool	is_quoted;
	t_bool	is_simplequote;
	//t_bool	is_aquote;
	//t_bool	is_closing;
}	t_esc;

typedef struct s_wd_desc
{
	char	*word;
	int		flags;
}	t_wd_desc;

// parsing

void	parsing(char *str, t_list **inputs);
char	**newlines(char *str, size_t *input_nb);
t_list	*break_into_words(char **inputs_array, size_t input_nb);

//utils

void	ft_error(void);
void	free_before_id(t_list *inputs);

//side

void	print_2d_array(char **str);
void	print_unidentified_tokens(size_t input_nb, t_list *inputs);

#endif
