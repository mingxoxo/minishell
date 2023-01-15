/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/15 18:37:05 by wonyang          ###   ########seoul.kr  */
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
		root = parse_line(str);
		if (!root)
			continue ;
		add_history(str);
		execute_tree(root);
		clear_node(root, del_t_token);
		free(str);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
		return (1);
	init_minishell_setting(env);
	routine();
	clear_envp(&(g_var.envp));
	return (g_var.status);
}
