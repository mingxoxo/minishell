/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/15 15:24:00 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// substitute_env

static char	*strjoin_cmd(t_tnode *node, size_t len)
{
	char	*new;

	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (node)
	{
		ft_strlcat(new, " ", len + 1);
		ft_strlcat(new, ((t_token *)(node->content))->str, len + 1);
		node = node->left;
	}
	return (new);
}

static t_error	cmd_subst_env(t_tnode *node, t_tnode *cmd)
{
	size_t	len;
	char	*line;

	len = 0;
	while (node)
	{
		if (env_first_step(node->content) == ERROR)
			return (ERROR);
		len += ft_strlen(((t_token *)(node->content))->str) + 1;
		node = node->left;
	}
	line = strjoin_cmd(cmd, len);
	if (!line)
		return (ERROR);
	if (env_second_step(line, cmd) == ERROR)
	{
		free(line);
		return (ERROR);
	}
	free(line);
	return (SCS);
}

t_error	subst_env(t_tnode *node)
{
	t_error	errno;

	if (!node)
		return (SCS);
	if (is_this_symbol(node->content, T_WORD))
		return (cmd_subst_env(node, node));
	errno = subst_env(node->left);
	errno = subst_env(node->right);
	return (errno);
}
