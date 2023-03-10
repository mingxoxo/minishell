/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:01:53 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/16 20:26:51 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_TREE_H
# define MAKE_TREE_H

# include "token.h"
# include "ds_tree.h"
# include <stdlib.h>
# include <stdbool.h>

# define OPEN_PAREN 1
# define CLOSE_PAREN -1
# define WILDCARD -42

// make_tree.c
t_tnode	*make_tree(t_list *head);
t_error	make_cmd(t_tnode **node, t_list **lst);

// make_node.c
t_error	make_new_node(t_tnode **node);
t_error	make_t_paren(t_tnode **node, t_list **lst);
t_error	make_dsv_node(t_tnode **node, t_list *lst);
t_error	make_t_io(t_tnode *node, t_list **lst);
t_error	make_t_word(t_tnode *node, t_list *lst);

// check_syntax.c
bool	is_correct_syntax(t_list *lst);

// check_type.c
bool	is_dsv_symbol(t_token *token);
bool	is_this_symbol(t_token *token, t_ttype type);
int		check_paren(t_token *token);

// check_tnode.c
t_list	*check_end_node(t_list **lst);
t_tnode	*check_parent(t_tnode *node, t_token *token);
t_tnode	*check_root(t_tnode *node);

// subst.c
t_error	subst(t_tnode *node);

// subst_env.c
t_error	cmd_subst_env(t_tnode *node, t_tnode *cmd);
t_error	r_file_subst_env(t_tnode *node);

// subst_env_*.c
t_error	env_first_step(t_token *token);
t_error	env_second_step(char *str, t_tnode *node);
t_error	subst_env_lst(t_token *token, int *arr, t_list **head);

// subst_wildcard.c
t_error	subst_wildcard(t_tnode *node);
void	resubst_wildcard(char *str);

// wildcard.c
t_error	wildcard(t_tnode *node);

// del_quote.c
t_error	del_quote(t_tnode *node);

#endif