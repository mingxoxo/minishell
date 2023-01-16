/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:20:31 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/16 17:01:47 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "make_tree.h"
#include "ds_tree.h"
#include "libft.h"

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

t_tnode	*parse_line(char *str)
{
	t_list	*lst;
	t_tnode	*node;

	lst = tokenization(str);
	if (!lst)
	{
		free(str);
		return (NULL);
	}
	if (!is_correct_syntax(lst->next))
	{
		ft_lstclear(&lst, del_t_token);
		free(str);
		return (NULL);
	}
	node = make_tree(lst->next);
	ft_lstclear(&lst, del_t_paren);
	if (subst(node) == ERROR || del_quote(node) == ERROR || !node)
	{
		free(str);
		return (NULL);
	}
	return (node);
}
