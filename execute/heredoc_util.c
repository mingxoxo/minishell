/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:42:06 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/12 22:39:45 by wonyang          ###   ########seoul.kr  */
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

static char	*make_heredoc_filename(void)
{
	char	*res;
	char	*path;
	int		fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	res = (char *)ft_calloc(sizeof(char), 31);
	read(fd, res, 30);
	if (!res || close(fd) == -1)
	{
		free(res);
		return (NULL);
	}
	path = ft_strjoin(".", res);
	free(res);
	return (path);
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

t_error	execute_heredoc(t_tnode *node)
{
	char	*delimiter;
	char	*file_name;
	int		fd;

	delimiter = ((t_token *)(node->left->content))->str;
	file_name = make_heredoc_filename();
	if (!file_name)
		return (ERROR);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ERROR);
	heredoc_readline(fd, delimiter);
	change_node_info(node, file_name);
	if (close(fd) == -1)
		return (ERROR);
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
