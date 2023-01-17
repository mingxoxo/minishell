/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:36:41 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 11:01:45 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "ds_tree.h"
#include "token.h"
#include "libft.h"
#include "execute.h"
#include "builtin.h"
#include "minishell.h"

extern t_global	g_var;

bool	is_builtin_cmd(t_tnode *node)
{
	t_token		*token;
	const char	cmd[7][7] = {"echo", "pwd", "cd", "env", "export", \
								"unset", "exit"};
	int			i;

	if (!node || !node->content)
	{
		ft_putendl_fd("is_builtin_cmd : node error", STDERR_FILENO);
		return (false);
	}
	token = (t_token *)node->content;
	if (token->type != T_WORD)
		return (false);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(token->str, (char *)(cmd[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	builtin_execve(char *path, char **argv, t_envp *envp, int child)
{
	if (ft_strcmp(path, "echo") == 0)
		return (ft_echo(argv));
	else if (ft_strcmp(path, "pwd") == 0)
		return (ft_pwd(argv));
	else if (ft_strcmp(path, "cd") == 0)
		return (ft_cd(argv, envp));
	else if (ft_strcmp(path, "env") == 0)
		return (ft_env(argv, envp));
	else if (ft_strcmp(path, "export") == 0)
		return (ft_export(argv, envp));
	else if (ft_strcmp(path, "unset") == 0)
		return (ft_unset(argv, envp));
	else if (ft_strcmp(path, "exit") == 0)
		return (ft_exit(argv, child));
	ft_putendl_fd("builtin_execve : invalid path", STDERR_FILENO);
	return (-1);
}

static t_error	set_redirection(int fd[2], t_tnode **cmd_list, char **cmd_argv)
{
	if (fd[0] < 0 || fd[1] < 0 || execute_all_heredoc(cmd_list) != SCS
		|| apply_redirections(cmd_list[0]) == ERROR)
	{
		close(fd[0]);
		close(fd[1]);
		ft_freesplit(cmd_argv);
		free(cmd_list);
		return (ERROR);
	}
	return (SCS);
}

t_error	execute_parent(t_tnode *node)
{
	t_tnode	**cmd_list;
	char	**cmd_argv;
	char	*path;
	int		fd[2];

	path = ((t_token *)(node->content))->str;
	cmd_argv = make_argv(node);
	if (!cmd_argv)
		return (ERROR);
	cmd_list = make_cmd_list(node);
	if (!cmd_list)
	{
		ft_freesplit(cmd_argv);
		return (ERROR);
	}
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (set_redirection(fd, cmd_list, cmd_argv) == ERROR)
		return (ERROR);
	g_var.status = builtin_execve(path, cmd_argv, &(g_var.envp), 0);
	ft_dup2(fd[0], STDIN_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
	ft_freesplit(cmd_argv);
	free(cmd_list);
	return (SCS);
}
