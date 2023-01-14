/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:04:00 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/13 22:12:25 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "return.h"
#include "ds_envp.h"

static void	sort_arr(char **arr, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	count_key(t_envp *envp)
{
	int		i;
	t_enode	*node;

	i = 0;
	node = envp->head;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

static void	print_line(t_envp *envp, char *key)
{
	char	*value;

	value = search_key_value(envp, key);
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	if (value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static char	**make_arr(t_envp *envp)
{
	int		i;
	t_enode	*node;
	char	**key_arr;
	int		len;

	len = count_key(envp);
	key_arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!key_arr)
		return (NULL);
	key_arr[len] = NULL;
	node = envp->head;
	i = 0;
	while (node)
	{
		key_arr[i] = node->key;
		i++;
		node = node->next;
	}
	sort_arr(key_arr, len);
	return (key_arr);
}

t_error	print_envp(t_envp *envp)
{
	int		i;
	char	**key_arr;

	key_arr = make_arr(envp);
	if (!key_arr)
		return (ERROR);
	i = 0;
	while (key_arr[i])
	{
		print_line(envp, key_arr[i]);
		i++;
	}
	free(key_arr);
	return (SCS);
}
