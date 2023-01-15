/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 23:33:05 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/15 19:10:27 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell.h"
#include "ds_envp.h"
#include "execute.h"
#include "libft.h"
#include "token.h"

extern t_global	g_var;

static void	child_execve(t_tnode *node, char *path, char **argv)
{
	char	*builtin;

	builtin = ((t_token *)(node->content))->str;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.old_term));
	if (is_builtin_cmd(node) == true)
		exit(builtin_execve(builtin, argv, &(g_var.envp), 1));
	execve(path, argv, g_var.envp.arr);
	exit(0);
}

static t_error	child_execute(t_tnode *cmd_node)
{
	char	**cmd_argv;
	char	*path;

	cmd_argv = make_argv(cmd_node);
	if (!cmd_argv)
		return (ERROR);
	if (apply_redirections(cmd_node) == ERROR
		|| make_cmd_path(cmd_argv[0], &path, g_var.envp.arr) == ERROR)
	{
		ft_freesplit(cmd_argv);
		return (ERROR);
	}
	if (ft_strcmp(cmd_argv[0], "") == 0
		|| (is_builtin_cmd(cmd_node) == false && !path))
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd_argv[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	child_execve(cmd_node, path, cmd_argv);
	return (SCS);
}

static pid_t	fork_child(t_tnode *cmd_node, int *before_fd)
{
	int		fd[2];
	pid_t	child_pid;
	int		tmp;

	if (pipe(fd) == -1)
		return (0);
	tmp = *before_fd;
	*before_fd = fd[0];
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
	{
		if (close(fd[0]) == -1
			|| (tmp != STDIN_FILENO && ft_dup2(tmp, STDIN_FILENO) == ERROR)
			|| ft_dup2(fd[1], STDOUT_FILENO) == ERROR
			|| child_execute(cmd_node) == ERROR)
			return (0);
	}
	if ((tmp != STDIN_FILENO && close(tmp) == -1)
		|| close(fd[1]) == -1)
		return (0);
	return (child_pid);
}

static pid_t	last_fork_child(t_tnode *cmd_node, int before_fd)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
	{
		if (before_fd != STDIN_FILENO
			&& ft_dup2(before_fd, STDIN_FILENO) == ERROR)
			return (0);
		if (child_execute(cmd_node) == ERROR)
			return (0);
	}
	if (before_fd != STDIN_FILENO && close(before_fd) == -1)
		return (0);
	return (child_pid);
}

t_error	create_childs(t_tnode **cmd_list, pid_t *pid_list)
{
	int	before_fd;
	int	i;

	before_fd = STDIN_FILENO;
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (cmd_list[i + 1])
	{
		pid_list[i] = fork_child(cmd_list[i], &before_fd);
		if (pid_list[i] == 0)
			return (ERROR);
		i++;
	}
	pid_list[i] = last_fork_child(cmd_list[i], before_fd);
	if (pid_list[i] == 0)
		return (ERROR);
	return (SCS);
}
