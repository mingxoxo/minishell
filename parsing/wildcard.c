/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/16 20:55:23 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"
#include <dirent.h>
#include <errno.h>

static t_token	*make_node_token(char *line, t_ttype type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(line);
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	return (token);
}

static bool	match_wcard(char *pattern, char *dname)
{
	int	len_p;
	int	len_w;
	int	nth;
	int	skip;

	nth = 0;
	len_p = ft_strlen(pattern);
	len_w = ft_strlen(dname);
	while (nth < len_p && nth < len_w && (pattern[nth] == dname[nth]))
		nth++;
	if (len_p == nth)
		return (nth == len_w);
	if (pattern[nth] == WILDCARD)
	{
		skip = 0;
		while (skip + nth <= len_w)
		{
			if (match_wcard(pattern + nth + 1, dname + skip + nth))
				return (true);
			skip += 1;
		}
	}
	return (false);
}

static t_error	add_wcard(t_tnode **node, t_token *token, int *cnt, char *dname)
{
	char	*new_str;
	t_token	*new;

	if (*cnt == 0)
	{
		new_str = ft_strdup(dname);
		if (new_str == NULL)
			return (ERROR);
		free(token->str);
		token->str = new_str;
	}
	else
	{
		new = make_node_token(dname, T_WORD);
		if (!new)
			return (ERROR);
		*node = add_lchild(*node, new);
		if (!(*node))
			return (ERROR);
	}
	(*cnt)++;
	return (SCS);
}

static t_error	check_wcard(t_tnode *node, t_token *token, char *str)
{
	int				cnt;
	DIR				*dir;
	struct dirent	*dirent;

	cnt = 0;
	dir = opendir(".");
	if (!dir)
		return (ERROR);
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (match_wcard(str, dirent->d_name)
			&& add_wcard(&node, token, &cnt, dirent->d_name) == ERROR)
		{
			closedir(dir);
			return (ERROR);
		}
	}
	if (!cnt)
		resubst_wildcard(token->str);
	if (closedir(dir) == -1 || errno)
		return (ERROR);
	return (SCS);
}

t_error	wildcard(t_tnode *node)
{
	char	*str;
	t_token	*token;

	if (!node)
		return (SCS);
	if (is_this_symbol(node->content, T_WORD))
	{
		if (wildcard(node->left) == ERROR)
			return (ERROR);
		token = (t_token *)(node->content);
		if (!ft_strchr(token->str, WILDCARD))
			return (SCS);
		str = ft_strdup(token->str);
		if (!str || check_wcard(node, token, str) == ERROR)
		{
			free(str);
			return (ERROR);
		}
		free(str);
		return (SCS);
	}
	free(NULL);
	if (wildcard(node->left) == ERROR || wildcard(node->right) == ERROR)
		return (ERROR);
	return (SCS);
}
