/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/15 18:06:54 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "ds_envp.h"
#include "ds_tree.h"
#include "builtin.h"
#include "make_tree.h"
#include "minishell.h"
#include "execute.h"

t_global	g_var;

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_tnode	*root;

	(void)argc;
	(void)argv;
	init_envp(&(g_var.envp), env);
	set_minishell_setting();
	while (1)
	{
		str = readline(PROMPT);
		if (str == NULL)
		{
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[12C", STDOUT_FILENO);
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (ft_strcmp(str, "") == 0)
		{
			free(str);
			continue ;
		}
		root = parse_line(str);
		if (!root)
			continue ;
		add_history(str);
		if (is_builtin_cmd(root))
			execute_builtin(root);
		else
			execute_cmds(root);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.new_term));
		set_signal_handling();
		clear_node(root, del_t_token);
		free(str);
		// system("leaks minishell | grep leaks");
	}
	clear_envp(&(g_var.envp));
	return (g_var.status);
}
