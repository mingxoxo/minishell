/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:36:33 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 14:04:48 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "ds_tree.h"
#include "token.h"
#include "return.h"
#include "libft.h"
#include "execute.h"

static t_error	set_infile(char *path, bool heredoc)
{
	int	in_fd;

	in_fd = open(path, O_RDONLY, 0644);
	if (in_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		return (ERROR);
	}
	if (heredoc)
		unlink(path);
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
		return (set_infile(path, false));
	else if (ft_strcmp(token->str, "<<") == 0)
		return (set_infile(path, true));
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
