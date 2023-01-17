/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:20:31 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/17 13:40:35 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "make_tree.h"
#include "ds_tree.h"
#include "libft.h"
#include "minishell.h"

extern t_global	g_var;

static void	del_t_paren(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)(content);
	if (!is_this_symbol(token, T_PAREN))
		return ;
	if (token->str)
		free(token->str);
	free(content);
	content = NULL;
}

static t_list	*pre_processing(char *str)
{
	t_list	*lst;

	lst = tokenization(str);
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
	{
		ft_lstclear(&lst, &del_t_token);
		return (NULL);
	}
	if (!is_correct_syntax(lst->next))
	{
		ft_lstclear(&lst, &del_t_token);
		return (NULL);
	}
	return (lst);
}

static t_error	post_processing(t_tnode *node)
{
	if (subst(node) == ERROR)
	{
		g_var.status = 1;
		return (ERROR);
	}
	if (del_quote(node) == ERROR)
	{
		g_var.status = 1;
		return (ERROR);
	}
	if (wildcard(node) == ERROR)
	{
		g_var.status = 1;
		return (ERROR);
	}
	if (!node)
		return (ERROR);
	return (SCS);
}

t_tnode	*parse_line(char *str)
{
	t_list	*lst;
	t_tnode	*node;

	lst = pre_processing(str);
	if (!lst)
	{
		free(str);
		g_var.status = 1;
		return (NULL);
	}
	node = make_tree(lst->next);
	ft_lstclear(&lst, &del_t_paren);
	if (post_processing(node) == ERROR)
	{
		free(str);
		clear_node(node, &del_t_token);
		return (NULL);
	}
	return (node);
}
