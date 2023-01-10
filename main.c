/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/10 17:54:12 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "ds_envp.h"
#include "builtin.h"

void	get_terminal_setting(void);
void	set_signal_handling(void);

int	main(int argc, char **argv, char **env)
{
	char	*str;

	get_terminal_setting();
	set_signal_handling();
	while (1)
	{
		str = readline("prompt :");
		if (str == NULL)
			exit(0);
		else if (ft_strcmp(str, "") == 0)
			continue ;
		add_history(str);
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
