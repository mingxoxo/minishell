/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:33:04 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/14 12:35:06 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "return.h"
# include "ds_envp.h"

int	ft_echo(char **argv);
int	ft_pwd(char **argv);
int	ft_cd(char **argv, t_envp *envp);
int	ft_env(char **argv, t_envp *envp);
int	ft_export(char **argv, t_envp *envp);
int	ft_unset(char **argv, t_envp *envp);
int	ft_exit(char **argv, int child);

#endif