/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:17:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/09 16:18:19 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_envp.h"

static int	count_envp(t_enode *node)
{
	int	cnt;

	cnt = 0;
	while (node)
	{
		if (node->value)
			cnt++;
		node = node->next;
	}
	return (cnt);
}

static t_error	init_arr(t_envp *envp, char ***arr)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = count_envp(envp->head);
	*arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!(*arr))
		return (ERROR);
	while (i < cnt + 1)
	{
		(*arr)[i] = NULL;
		i++;
	}
	return (SCS);
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

char	**cast_envp_arr(t_envp *envp)
{
	int		i;
	t_enode	*node;
	char	**arr;

	if (init_arr(envp, &arr) == ERROR)
		return (NULL);
	i = 0;
	node = envp->head;
	while (node)
	{
		if (node->value)
		{
			arr[i] = make_format(node);
			if (!(arr[i]))
			{
				ft_freesplit(arr);
				return (NULL);
			}
			i++;
		}
		node = node->next;
	}
	return (arr);
}
