/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/09 16:27:05 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ds_envp.h"
#include "builtin.h"

int	main(int argc, char **argv, char **env)
{
	t_envp	envp;

	init_envp(&envp, env);
	ft_exit(argv);
	// ft_cd(argv, &envp);
	// printf("PWD : %s\n", search_key_value(&envp, "PWD"));
	// printf("OLDPWD : %s\n", search_key_value(&envp, "OLDPWD"));
	return (0);
}
