/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:30:55 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/13 15:15:01 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "execute.h"
#include "libft.h"

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
		i++;
	}
	return (status / 256);
}

t_error	execute_cmds(t_tnode *root)
{
	t_tnode **cmd_list;
	pid_t	*pid_list;

	cmd_list = make_cmd_list(root);
	if (!cmd_list)
		return (ERROR);
	pid_list = empty_pid_list(cmd_list);
	if (!pid_list
		|| execute_all_heredoc(cmd_list) == ERROR
		|| create_childs(cmd_list, pid_list) == ERROR)
	{
		free(pid_list);
		return (ERROR);
	}
	wait_proc(pid_list);
	free(pid_list);
	free(cmd_list);
	return (SCS);
}
