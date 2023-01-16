/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/16 20:27:17 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// substitute_wildcard

t_error	subst_wildcard(t_tnode *node)
{
	char	*str;
	char	*pair;

	while (node)
	{
		str = ((t_token *)(node->content))->str;
		while (*str)
		{
			if (*str == '\"' || *str == '\'')
			{
				pair = ft_strchr(str + 1, *str);
				if (pair)
					str = pair;
			}
			else if (*str == '*')
				*str *= -1;
			str++;
		}
		node = node->left;
	}
	return (SCS);
}

void	resubst_wildcard(char *str)
{
	while (*str)
	{
		if (*str == WILDCARD)
			*str *= -1;
		str++;
	}
}
