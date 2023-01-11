/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:01:53 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/11 23:11:13 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_TREE_H
# define MAKE_TREE_H

# include "token.h"
# include "ds_tree.h"
# include <stdlib.h>
# include <stdbool.h>

// make_tree.c
t_tnode	*make_tree(t_list *head);

// make_node.c
t_error	make_new_node(t_tnode **node);
t_error	make_t_paren(t_tnode **node, t_list **lst);
t_error	make_dsv_node(t_tnode **node, t_list *lst);
t_error	make_t_io(t_tnode *node, t_list **lst);
t_error	make_t_word(t_tnode *node, t_list *lst);

// check.c
bool	is_dsv_symbol(t_token *token);
bool	is_this_symbol(t_token *token, t_ttype type);
t_list	*check_end_node(t_list **lst);
t_tnode	*check_parent(t_tnode *node, t_token *token);
t_tnode	*check_root(t_tnode *node);

#endif