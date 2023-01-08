/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:17:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/08 16:59:27 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_envp.h"

void	init_envp(t_envp *envp, char **arr)
{
	envp->cnt = 0;
	envp->change = 1;
	envp->arr = NULL;
	envp->head = NULL;
	cast_envp_list(envp, arr);
}

t_enode	*init_enode(char *key, char *value)
{
	t_enode	*new;

	new = (t_enode *)malloc(sizeof(t_enode));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

static void	set_value(t_enode *node, char *value)
{
	if (!node)
	{
		printf("[ds_envp]set_value error: node is NULL\n");
		return ;
	}
	node->value = value;
}

t_error	set_key_value(t_envp *envp, char *key, char *value)
{
	t_enode	*node;

	node = search_key_enode(envp, key);
	if (node)
	{
		del_value(node);
		set_value(node, value);
		return (SCS);
	}
	node = init_enode(key, value);
	if (!node)
	{
		perror("[ds_envp]set_key_value");
		return (ERROR);
	}
	add_last(envp, node);
	return (SCS);
}
