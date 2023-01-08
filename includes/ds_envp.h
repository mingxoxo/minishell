/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds_envp.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:17:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/08 17:20:50 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DS_ENVP_H
# define DS_ENVP_H

# include <stdio.h>
# include <stdlib.h>
# include  "../includes/return.h"
# include "../libft/libft.h"

typedef struct s_enode
{
	char			*key;
	char			*value;
	struct s_enode	*prev;
	struct s_enode	*next;
}					t_enode;

typedef struct s_envp
{
	struct s_enode	*head;
	int				cnt;
	int				change;
	char			**arr;
}					t_envp;

// init.c
void	init_envp(t_envp *envp, char **arr);
t_enode	*init_enode(char *key, char *value);
t_error	set_key_value(t_envp *envp, char *key, char *value);

// add.c
void	add_last(t_envp *envp, t_enode *new);
void	add_first(t_envp *envp, t_enode *new);

// delete.c
void	del_value(t_enode *node);
int		del_key_enode(t_envp *envp, char *key);
void	clear_enode(t_envp *envp);

// search.c
t_enode	*search_key_enode(t_envp *envp, char *key);
char	*search_key_value(t_envp *envp, char *key);

// cast_*.c
char	**cast_envp(t_envp *envp);
t_error	cast_envp_line(t_envp *envp, char *line);
t_error	cast_envp_list(t_envp *envp, char **arr);

#endif