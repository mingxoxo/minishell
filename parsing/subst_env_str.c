/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:41:40 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 18:30:14 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"
#include "minishell.h"

extern t_global	g_var;

t_error	subst_env_str(t_token *token)
{
	char	*new;
	char	*value;

	new = NULL;
	if (ft_strcmp(token->str, "$?") == 0)
		new = ft_itoa(g_var.status);
	else
	{
		value = search_key_value(&(g_var.envp), token->str);
		if (value)
			new = ft_strdup(value);
		else
			new = ft_strdup("");
	}
	if (!new)
		return (ERROR);
	free(token->str);
	token->str = new;
	return (SCS);
}
