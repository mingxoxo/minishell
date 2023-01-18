/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 14:46:49 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ds_envp.h"

t_enode	*search_key_enode(t_envp *envp, char *key)
{
	t_enode	*node;

	node = envp->head;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	*search_key_value(t_envp *envp, char *key)
{
	t_enode	*node;

	node = search_key_enode(envp, key);
	if (!node)
		return (NULL);
	return (node->value);
}
