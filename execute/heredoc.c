/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:40:41 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/16 18:40:52 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include "ds_tree.h"
#include "token.h"
#include "libft.h"
#include "execute.h"
#include "minishell.h"

extern t_global	g_var;

static bool	is_heredoc_node(t_tnode *node)
{
	t_token	*token;

	token = (t_token *)(node->content);
	if (token->type == T_IO && ft_strcmp(token->str, "<<") == 0)
		return (true);
	return (false);
}

t_error	execute_all_heredoc(t_tnode **cmd_list)
{
	int		i;
	t_tnode	*node;

	i = 0;

	if (signal(SIGINT, sigint_handler_heredoc) == SIG_ERR)
		return (ERROR);
	while (cmd_list[i])
	{
		node = cmd_list[i];
		while (node)
		{
			if (is_heredoc_node(node) && execute_heredoc(node) == ERROR)
			{
				perror("");
				ft_putendl_fd("heredoc error", 2);
				return (ERROR);
			}
			if (g_var.is_signal)
			{
				g_var.is_signal = 0;
				signal(SIGINT, sigint_handler_prompt);
				return (FAIL);
			}
			node = node->right;
		}
		i++;
	}
	if (signal(SIGINT, sigint_handler_prompt) == SIG_ERR)
		return (ERROR);
	return (SCS);
}
