/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 22:13:46 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/07 16:39:43 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_envp.h"

void	add_last(t_envp *envp, t_enode *new)
{
	t_enode	*last;

	envp->cnt++;
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

void	add_first(t_envp *envp, t_enode *new)
{
	t_enode	*first;

	envp->cnt++;
	first = envp->head;
	if (first == NULL)
	{
		envp->head = new;
		return ;
	}
	new->prev = first;
	if (first->next)
		first->next->prev = new;
	new->next = first->next;
	first->next = new;
}
