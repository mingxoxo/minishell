/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ds_envp.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:17:28 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/17 14:47:15 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef DS_ENVP_H
# define DS_ENVP_H

# include <stdio.h>
# include <stdlib.h>
# include  "return.h"
# include "libft.h"

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
	char			**arr;
}					t_envp;

// init.c
t_error	init_envp(t_envp *envp, char **arr);
t_enode	*init_enode(char *key, char *value);
t_error	refresh_arr(t_envp *envp);

// set.c
t_error	set_key_value(t_envp *envp, char *key, char *value);
t_error	set_env(t_envp *envp, char *ori_key, char *ori_value);
t_error	set_export(t_envp *envp, char *line);

// delete.c
void	del_value(t_enode *node);
t_error	del_key_enode(t_envp *envp, char *key);
void	clear_envp(t_envp *envp);

// search.c
t_enode	*search_key_enode(t_envp *envp, char *key);
char	*search_key_value(t_envp *envp, char *key);

// cast_*.c
t_error	get_key(char *line, char **key);
char	**cast_envp_arr(t_envp *envp);
t_error	cast_envp_line(t_envp *envp, char *line);
t_error	cast_envp_list(t_envp *envp, char **arr);

#endif