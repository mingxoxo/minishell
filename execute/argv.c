/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:39:34 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/11 17:12:40 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ds_tree.h"
#include "token.h"
#include "libft.h"

static int	count_argument(t_tnode *node)
{
	int	count;

	count = 0;
	while (node)
	{
		count++;
		node = node->left;
	}
	return (count);
}

char	**make_argv(t_tnode *node)
{
	t_token	*token;	
	char	**argv;
	int		i;

	argv = (char **)ft_calloc(count_argument(node) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (node)
	{
		token = (t_token *)node->content;
		argv[i] = ft_strdup(token->str);
		if (!(argv[i]))
		{
			ft_freesplit(argv);
			return (NULL);
		}
		node = node->left;
		i++;
	}
	return (argv);
}
