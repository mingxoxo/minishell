/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 15:22:01 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include "token.h"

t_global	g_var;

void	run_code(char *str)
{
	t_tnode	*root;

	root = parse_line(str);
	if (!root)
		return ;
	execute(root);
	clear_node(root, &del_t_token);
}

static void	routine(void)
{
	char	*str;
	t_tnode	*root;

	while (1)
	{
		str = readline(PROMPT);
		if (str == NULL)
		{
			ft_putendl_fd("\x1b[1A\033[12Cexit", STDOUT_FILENO);
			break ;
		}
		if (ft_strcmp(str, "") == 0)
		{
			free(str);
			continue ;
		}
		add_history(str);
		root = parse_line(str);
		if (!root)
			continue ;
		execute(root);
		clear_node(root, &del_t_token);
		free(str);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1 || init_minishell_setting(env) == ERROR)
		return (1);
	routine();
	clear_envp(&(g_var.envp));
	free(g_var.tmp_path);
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.old_term));
	return (g_var.status);
}
