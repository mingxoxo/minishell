/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/09 16:07:56 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include "libft.h"
#include "ds_envp.h"

int	main(int argc, char **argv, char **envp)
{
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
	return (0);
}
