/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:42:06 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/13 13:01:14 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "ds_tree.h"
#include "token.h"
#include "libft.h"
#include "execute.h"
#include "return.h"

static char	*make_heredoc_filename(int i)
{
	char	*path[2];
	char	*tmp;

	path[0] = "/tmp/.heredoc_";
	tmp = ft_itoa(i);
	if (tmp)
	{
		path[0] = ft_strjoin(path[0], tmp);
		free(tmp);
	}
	tmp = ttyname(STDIN_FILENO);
	if (tmp)
	{
		path[1] = path[0];
		path[0] = ft_strjoin(path[1], tmp + 5);
		free(path[1]);
	}
	return (path[0]);
}

static void	heredoc_readline(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static void	change_node_info(t_tnode *node, char *filename)
{
	t_token	*path;

	path = (t_token *)node->left->content;
	free(path->str);
	path->str = filename;
}

t_error	execute_heredoc(t_tnode *node, int *i)
{
	char	*delimiter;
	char	*file_name;
	int		fd;

	delimiter = ((t_token *)(node->left->content))->str;
	file_name = make_heredoc_filename(*i);
	if (!file_name)
		return (ERROR);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ERROR);
	heredoc_readline(fd, delimiter);
	change_node_info(node, file_name);
	if (close(fd) == -1)
		return (ERROR);
	*i += 1;
	return (SCS);
}

void	remove_heredoc_files(char **file_list)
{
	int	i;

	i = 0;
	while (file_list[i])
	{
		unlink(file_list[i]);
		free(file_list[i]);
		i++;
	}
	free(file_list);
}
