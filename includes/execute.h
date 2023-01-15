/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:33:04 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/15 22:11:12 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdbool.h>
# include "ds_tree.h"
# include "return.h"
# include "ds_envp.h"

// builtin.c
bool	is_builtin_cmd(t_tnode *node);
int		builtin_execve(char *path, char **argv, t_envp *envp, int child);
t_error	execute_parent(t_tnode *node);

// preprocess.c
t_tnode	**make_cmd_list(t_tnode *root);

// execute.c
void	execute(t_tnode *node);

// child.c
t_error	create_childs(t_tnode **cmd_list, pid_t *pid_list);

// argv.c
char	**make_argv(t_tnode *node);

// redirection.c
t_error	apply_redirections(t_tnode *node);

// path.c
t_error	make_cmd_path(char *cmd_name, char **path, char **envp);

// heredoc.c
t_error	execute_all_heredoc(t_tnode **cmd_list);

// heredoc_util.c
t_error	execute_heredoc(t_tnode *node);

// util.c
t_error	ft_dup2(int fd1, int fd2);

#endif