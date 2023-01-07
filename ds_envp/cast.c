/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:17:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/07 17:36:21 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_envp.h"

static void	init_arr(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		arr[i] = NULL;
		i++;
	}
}

static char	*make_format(t_enode *node)
{
	size_t	len;
	char	*line;

	len = ft_strlen(node->key) + ft_strlen(node->value) + 2;
	line = (char *)malloc(sizeof(char) * (len));
	if (!line)
		return (NULL);
	ft_strlcpy(line, node->key, len);
	ft_strlcat(line, "=", len);
	ft_strlcat(line, node->value, len);
	return (line);
}

char	**cast_envp(t_envp *envp)
{
	int		i;
	t_enode	*node;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * (envp->cnt + 1));
	if (!arr)
		return (NULL);
	init_arr(arr, envp->cnt + 1);
	i = 0;
	node = envp->head;
	while (i < envp->cnt)
	{
		arr[i] = make_format(node);
		if (!(arr[i]))
		{
			ft_freesplit(arr);
			return (NULL);
		}
		i++;
		node = node->next;
	}
	return (arr);
}
