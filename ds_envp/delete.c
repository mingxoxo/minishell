/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:17:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/17 14:46:49 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ds_envp.h"

static void	del_key(t_enode *node)
{
	if (!node)
	{
		printf("[ds_envp]del_key error: node is NULL\n");
		return ;
	}
	if (node->key)
		free(node->key);
	node->key = NULL;
}

void	del_value(t_enode *node)
{
	if (!node)
	{
		printf("[ds_envp]del_value error: node is NULL\n");
		return ;
	}
	if (node->value)
		free(node->value);
	node->value = NULL;
}

static void	del_enode(t_envp *envp, t_enode *node)
{
	t_enode	*del_prev;
	t_enode	*del_next;

	if (!node)
	{
		printf("[ds_envp]del_enode error: node is NULL.\n");
		return ;
	}
	if (envp->head == node)
		envp->head = node->next;
	del_prev = node->prev;
	del_next = node->next;
	if (del_prev)
		del_prev->next = del_next;
	if (del_next)
		del_next->prev = del_prev;
	del_key(node);
	del_value(node);
	free(node);
	node = NULL;
}

t_error	del_key_enode(t_envp *envp, char *key)
{
	t_enode	*node;

	node = search_key_enode(envp, key);
	if (!node)
		return (FAIL);
	del_enode(envp, node);
	return (refresh_arr(envp));
}

void	clear_envp(t_envp *envp)
{
	t_enode	*tmp;
	t_enode	*node;

	tmp = envp->head;
	while (tmp)
	{
		node = tmp;
		tmp = tmp->next;
		del_enode(envp, node);
	}
	if (envp->arr)
		ft_freesplit(envp->arr);
	envp->head = NULL;
	envp->arr = NULL;
}
