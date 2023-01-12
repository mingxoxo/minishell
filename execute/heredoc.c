/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:40:41 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/12 17:19:44 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "ds_tree.h"
#include "token.h"
#include "libft.h"
#include "execute.h"

static int	count_heredoc(t_tnode *node)
{
	t_token	*token;
	int		count;

	count = 0;
	while (node)
	{
		token = (t_token *)(node->content);
		if (token->type == T_IO && ft_strcmp(token->str, "<<") == 0)
			count++;
		node = node->right;
	}
	return (count);
}

static char	**empty_tmpfile_list(t_tnode **cmd_list)
{
	char	**tmpfile_list;
	int		i;
	int		total;

	if (!cmd_list)
		return (NULL);
	i = 0;
	total = 0;
	while (cmd_list[i])
	{
		total += count_heredoc(cmd_list[i]);
		i++;
	}
	tmpfile_list = (char **)ft_calloc(total + 1, sizeof(char *));
	return (tmpfile_list);
}

static bool	is_heredoc_node(t_tnode *node)
{
	t_token	*token;

	token = (t_token *)(node->content);
	if (token->type == T_IO && ft_strcmp(token->str, "<<") == 0)
		return (true);
	return (false);
}

char	**execute_all_heredoc(t_tnode **cmd_list)
{
	char	**tmpfile_list;
	int		i;
	int		file_cnt;
	t_tnode	*node;

	tmpfile_list = empty_tmpfile_list(cmd_list);
	if (!tmpfile_list)
		return (NULL);
	i = 0;
	file_cnt = 0;
	while (cmd_list[i])
	{
		node = cmd_list[i];
		while (node)
		{
			if (is_heredoc_node(node))
			{
				tmpfile_list[file_cnt] = execute_heredoc(node);
				if (tmpfile_list[file_cnt] == NULL)
					break ;
				file_cnt++;
			}
			node = node->right;
		}
		i++;
	}
	return (tmpfile_list);
}
