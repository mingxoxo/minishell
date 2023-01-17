/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:30:55 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 11:35:36 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"
#include "execute.h"
#include "libft.h"
#include "make_tree.h"

extern t_global	g_var;

static pid_t	*empty_pid_list(t_tnode **cmd_list)
{
	pid_t	*pid_list;
	int		i;

	i = 0;
	while (cmd_list[i])
		i++;
	pid_list = (pid_t *)ft_calloc(i + 1, sizeof(pid_t));
	return (pid_list);
}

static int	wait_proc(pid_t *pid_list)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (pid_list[i])
	{
		waitpid(pid_list[i], &status, 0);
		if (0 < status && status < 256)
			status = (128 + status) * 256;
		i++;
	}
	return (status / 256);
}

static t_error	execute_child(t_tnode *root)
{
	t_tnode	**cmd_list;
	pid_t	*pid_list;

	cmd_list = make_cmd_list(root);
	if (!cmd_list)
		return (ERROR);
	pid_list = empty_pid_list(cmd_list);
	if (!pid_list
		|| execute_all_heredoc(cmd_list) != SCS
		|| create_childs(cmd_list, pid_list) == ERROR)
	{
		free(pid_list);
		free(cmd_list);
		return (ERROR);
	}
	g_var.status = wait_proc(pid_list);
	free(pid_list);
	free(cmd_list);
	return (SCS);
}

static void	execute_tree(t_tnode *root)
{
	t_error	errno;

	if (is_builtin_cmd(root))
		errno = execute_parent(root);
	else
		errno = execute_child(root);
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.new_term));
	signal(SIGINT, sigint_handler_prompt);
	if (errno)
		g_var.status = 1;
}

void	execute(t_tnode *node)
{
	t_token	*token;

	if (!node)
		return ;
	token = (t_token *)(node->content);
	if (!is_this_symbol(token, T_OPER))
	{
		execute_tree(node);
		return ;
	}
	execute(node->left);
	if (ft_strcmp(token->str, "&&") == 0 && g_var.status == 0)
		execute(node->right);
	else if (ft_strcmp(token->str, "||") == 0 && g_var.status != 0)
		execute(node->right);
}
