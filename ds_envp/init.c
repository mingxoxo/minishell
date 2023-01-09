/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:17:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/09 16:07:51 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_envp.h"

t_error	init_envp(t_envp *envp, char **arr)
{
	t_error	errno;

	envp->arr = NULL;
	envp->head = NULL;
	errno = cast_envp_list(envp, arr);
	if (errno != SCS)
		return (errno);
	envp->arr = cast_envp_arr(envp);
	if (!(envp->arr))
		return (ERROR);
	return (SCS);
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

t_error	refresh_arr(t_envp *envp)
{
	if (envp->arr)
		ft_freesplit(envp->arr);
	envp->arr = cast_envp_arr(envp);
	if (!(envp->arr))
		return (ERROR);
	return (SCS);
}
