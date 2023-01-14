/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 16:37:31 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"
#include "minishell.h"

// substitute_env

extern t_global	g_var;

void	handling_envp(int *arr, int len)
{
	int	i;

	i = 1;
	while (i < len)
	{
		if (arr[i] == T_WORD && arr[i - 1] / 10 == T_DOLLER)
		{
			arr[i - 1] = T_DOLLER * 10 + 1;
			arr[i] = T_ENVP * 10;
		}
		else if (arr[i] == T_WORD && arr[i - 1] == T_ENVP * 10)
			arr[i] = T_ENVP * 10;
		i++;
	}
	i = 0;
	while (i < len)
	{
		if (arr[i] == T_DOLLER * 10)
			arr[i] = 0;
		i++;
	}
}

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
		if (!value)
		{
			free(token->str);
			token->str = NULL;
			return (SCS);
		}
		new = ft_strdup(value);
	}
	if (!new)
		return (ERROR);
	free(token->str);
	token->str = new;
	return (SCS);
}

t_error	subst_env_lst(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = (t_token *)(lst->content);
		lst = lst->next;
		if (token->type != T_ENVP)
			continue ;
		if (subst_env_str(token) == ERROR)
			return (ERROR);
	}
	return (SCS);
}

static t_error	cmd_subst_env(t_tnode *node)
{
	while (node)
	{
		if (env_first_step(node->content) == ERROR)
			return (ERROR);
		node = node->left;
	}
	return (SCS);
}

t_error	subst_env(t_tnode *node)
{
	t_error	errno;

	if (!node)
		return (SCS);
	if (is_this_symbol(node->content, T_WORD))
		return (cmd_subst_env(node));
	errno = subst_env(node->left);
	errno = subst_env(node->right);
	return (errno);
}
