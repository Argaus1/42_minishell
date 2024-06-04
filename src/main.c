/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulore <aboulore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:58:43 by abernade          #+#    #+#             */
/*   Updated: 2024/06/04 15:06:17 by aboulore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_status;

static char *get_prompt(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		strerror(errno);
		exit(errno);
	}
	prompt = ft_strjoin(cwd, "$ ");
	free(cwd);
	return (prompt);
}

static char	*select_prompt(void)
{
	char			*prompt;
	char			*line;

	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
	return (line);
}

static void	shell_prompt(t_list **env, int ac)
{
	t_list		*tokens;
	char		*line;
	t_pipeline	*pipeline;

	set_rl_signals();
   	line = select_prompt();
	set_exec_signals();
	if (g_status)
	{
		update_env_exit_code(env, g_status + 128);
		g_status = 0;
	}
	if (ft_strlen(line))
	{
		if (parsing(ft_strdup(line), &tokens, *env, &pipeline) == 0)
		{
			pipeline->cmd_line = line;
			execute_pipeline(pipeline);
		}
		else
			pipeline = NULL;
	}
	if (ft_strlen(line))
	{
		add_history(line);
		free(line);
		if (pipeline)
		{
			*env = pipeline->envp;
			free(pipeline);
		}
		shell_prompt(env, ac);
	}
	else if (line)
	{
		free(line);
		shell_prompt(env, ac);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;

	(void)av;
	g_status = 0;
	env = NULL;
	
	set_hashtable(envp, &env);
	shell_prompt(&env, ac);
	ft_lstclear(&env, &del_member);
	ft_putstr_fd("exit\n", 1);
	return (0);
}
