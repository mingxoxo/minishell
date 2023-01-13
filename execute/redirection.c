/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:36:33 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/13 12:53:35 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "ds_tree.h"
#include "token.h"
#include "return.h"
#include "libft.h"
#include "execute.h"

static t_error	set_infile_normal(char *path)
{
	int	in_fd;

	in_fd = open(path, O_RDONLY, 0644);
	if (in_fd == -1)
	{
		perror(path);
		return (ERROR);
	}
	return (ft_dup2(in_fd, STDIN_FILENO));
}

static t_error	set_infile_heredoc(char *path)
{
	int	in_fd;

	in_fd = open(path, O_RDONLY, 0644);
	if (in_fd == -1)
	{
		perror(path);
		return (ERROR);
	}
	// unlink(path);
	return (ft_dup2(in_fd, STDIN_FILENO));
}

static t_error	set_outfile_trunc(char *path)
{
	int	out_fd;

	out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		return (ERROR);
	return (ft_dup2(out_fd, STDOUT_FILENO));
}

static t_error	set_outfile_append(char *path)
{
	int	out_fd;

	out_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd == -1)
		return (ERROR);
	return (ft_dup2(out_fd, STDOUT_FILENO));
}

t_error	redirection(t_tnode *node)
{
	t_token	*token;
	char	*path;

	path = ((t_token *)(node->left->content))->str;
	token = (t_token *)node->content;
	if (ft_strcmp(token->str, "<") == 0)
		return (set_infile_normal(path));
	else if (ft_strcmp(token->str, "<<") == 0)
		return (set_infile_heredoc(path));
	else if (ft_strcmp(token->str, ">") == 0)
		return (set_outfile_trunc(path));
	else if (ft_strcmp(token->str, ">>") == 0)
		return (set_outfile_append(path));
	return (ERROR);
}

t_error	apply_redirections(t_tnode *node)
{
	if (!node)
		return (ERROR);
	node = node->right;
	while (node)
	{
		if (redirection(node) == ERROR)
			return (ERROR);
		node = node->right;
	}
	return (SCS);
}
