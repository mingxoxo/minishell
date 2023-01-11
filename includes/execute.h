/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:33:04 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/11 22:21:26 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "ds_tree.h"
#include "return.h"

// argv.c
char	**make_argv(t_tnode *node);

// redirection.c
t_error	redirection(t_tnode *node);

// path.c
t_error	make_cmd_path(char *cmd_name, char **path, char **envp);

// heredoc.c
char	**execute_all_heredoc(t_tnode **cmd_list);

// heredoc_util.c
char	*execute_heredoc(t_tnode *node);

// util.c
t_error	ft_dup2(int fd1, int fd2);

#endif