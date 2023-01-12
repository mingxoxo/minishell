/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:33:50 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/11 19:38:43 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DS_TREE_H
# define DS_TREE_H

# include <stdlib.h>
# include <stdio.h>

typedef enum e_position{
	NONE,
	LEFT,
	RIGHT,
}	t_pos;

typedef struct s_node
{
	void			*content;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
}					t_tnode;

// init.c
t_tnode	*init_node(void *content);
void	set_content(t_tnode *node, void *content);
void	set_lchild(t_tnode *node, t_tnode *left);
void	set_rchild(t_tnode *node, t_tnode *right);

// add.c
t_tnode	*add_lchild(t_tnode *node, void *content);
t_tnode	*add_rchild(t_tnode *node, void *content);

// delete.c
void	del_node(t_tnode *node, void (*del)(void *));
t_tnode	*clear_node(t_tnode *node, void (*del)(void *));
void	*pop_node(t_tnode *node);

// search.c
void	preorder(t_tnode *node, int level, char *direction);
void	inorder(t_tnode *node);

#endif