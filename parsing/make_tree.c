/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:13:27 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/11 23:01:49 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

t_error	make_cmd(t_tnode **node, t_list **lst)
{
	t_error	errno;

	errno = SCS;
	if (!(*node) || is_dsv_symbol((*node)->content))
	{
		if (make_new_node(node) == ERROR)
			return (ERROR);
	}
	if (is_this_symbol((*lst)->content, T_IO))
		errno = make_t_io((*node), lst);
	else if (is_this_symbol((*lst)->content, T_WORD))
		errno = make_t_word((*node), (*lst));
	return (errno);
}

t_tnode	*make_tree(t_list *head)
{
	t_list	*lst;
	t_tnode	*node;
	t_error	errno;

	node = NULL;
	lst = head;
	while (lst)
	{
		if (is_this_symbol(lst->content, T_PAREN))
			errno = make_t_paren(&node, &lst);
		else if (is_dsv_symbol(lst->content))
			errno = make_dsv_node(&node, lst);
		else
			errno = make_cmd(&node, &lst);
		if (errno == ERROR)
			return (clear_node(check_root(node), NULL));
		lst = lst->next;
	}
	return (check_root(node));
}
