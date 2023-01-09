/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/09 16:27:05 by wonyang          ###   ########seoul.kr  */
=======
/*   Updated: 2023/01/09 16:07:56 by wonyang          ###   ########seoul.kr  */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include "libft.h"
#include "ds_envp.h"
#include "builtin.h"

int	main(int argc, char **argv, char **env)
{
<<<<<<< HEAD
	t_envp	envp;

	init_envp(&envp, env);
	ft_exit(argv);
	// ft_cd(argv, &envp);
	// printf("PWD : %s\n", search_key_value(&envp, "PWD"));
	// printf("OLDPWD : %s\n", search_key_value(&envp, "OLDPWD"));
=======
	char	*str;

	while (1)
	{
		str = readline("prompt :");
		if (ft_strcmp(str, "exit") == 0)
			exit(0);
		add_history(str);
		printf("%s\n", str);
		free(str);
	}
>>>>>>> main
	return (0);
}
