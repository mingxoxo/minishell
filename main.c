/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/10 16:39:35 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "ds_envp.h"
#include "builtin.h"
#include "token.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;

	while (1)
	{
		str = readline("prompt$ ");
		if (ft_strcmp(str, "exit") == 0)
			exit(0);
		add_history(str);
		printf("%s\n", str);
		tokenization(str);
		free(str);
	}
	return (0);
}
