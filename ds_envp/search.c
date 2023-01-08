/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/07 17:03:25 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_envp.h"

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
