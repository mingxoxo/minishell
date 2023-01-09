/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:33:04 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/09 16:26:53 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "return.h"
# include "ds_envp.h"

int		ft_echo(char **argv);
t_error	ft_pwd(char **argv);
t_error	ft_cd(char **argv, t_envp *envp);
int		ft_env(char **argv, t_envp *envp);
t_error	ft_unset(char **argv, t_envp *envp);
int		ft_exit(char **argv);

#endif