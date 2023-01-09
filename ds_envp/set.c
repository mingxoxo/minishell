/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:17:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/09 16:22:32 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_envp.h"

static void	add_last(t_envp *envp, t_enode *new)
{
	t_enode	*last;

	last = envp->head;
	if (last == NULL)
	{
		envp->head = new;
		return ;
	}
	while (last->next)
		last = last->next;
	new->prev = last;
	last->next = new;
}

t_error	set_key_value(t_envp *envp, char *key, char *value)
{
	t_enode	*node;

	node = search_key_enode(envp, key);
	if (node)
	{
		free(key);
		if (!value)
			return (FAIL);
		del_value(node);
		node->value = value;
		return (SCS);
	}
	node = init_enode(key, value);
	if (!node)
		return (ERROR);
	add_last(envp, node);
	return (SCS);
}

t_error	set_env(t_envp *envp, char *ori_key, char *ori_value)
{
	t_error	errno;
	char	*key;
	char	*value;

	key = ft_strdup(ori_key);
	if (!key)
		return (ERROR);
	if (!ori_value)
		return (set_key_value(envp, key, NULL));
	value = ft_strdup(ori_value);
	if (!value)
		return (ERROR);
	errno = set_key_value(envp, key, value);
	if (errno)
		return (errno);
	return (refresh_arr(envp));
}

t_error	set_export(t_envp *envp, char *line)
{
	t_error	errno;

	errno = cast_envp_line(envp, line);
	if (errno)
		return (errno);
	return (refresh_arr(envp));
}
