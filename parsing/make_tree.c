/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:13:27 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/11 22:33:20 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

void	print_lst(t_list *lst);

t_error	make_cmd(t_tnode **node, t_list **lst)
{
	t_error	errno;

	if (!node || is_root_symbol(node->content))
	{
		if (make_new_node(&node) == ERROR)
			return (ERROR);
	}
	if (is_this_symbol((*lst)->content, T_IO))
		errno = make_t_io(node, lst);
	else if (is_this_symbol((*lst)->content, T_WORD))
		errno = make_t_word(node, (*lst));
	return (errno);
}

t_tnode	*make_tree(t_list *lst)
{
	t_list	*tmp;
	t_tnode	*node;
	t_error	errno;

	node = NULL;
	tmp = lst;
	while (tmp)
	{
		if (is_this_symbol(tmp->content, T_PAREN))
			errno = make_t_paren(&node, &tmp);
		else if (is_root_symbol(tmp->content))
			errno = make_cross_node(&node, tmp);
		else
			errno = make_cmd(&node, tmp);
		if (errno == ERROR)
			return (clear_node(check_root(node), NULL));
		tmp = tmp->next;
	}
	return (check_root(node));
}
