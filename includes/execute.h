/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:33:04 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/11 17:31:27 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "ds_tree.h"
#include "return.h"

// argv.c
char	**make_argv(t_tnode *node);
t_error	make_cmd_path(char *cmd_name, char **path, char **envp);

#endif