/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/11 17:05:51 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "ds_envp.h"
#include "builtin.h"
#include "minishell.h"
#include "token.h"

static void	print_lst(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = (t_token *)(lst->content);
		printf("[%d] [%s]\n", token->type, token->str);
		lst = lst->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_list	*lst;

	(void)argc;
	(void)argv;
	(void)env;
	set_minishell_setting();
	lst = NULL;
	while (1)
	{
		str = readline("prompt$ ");
		if (str == NULL)
			exit(0);
		else if (ft_strcmp(str, "") == 0)
			continue ;
		add_history(str);
		printf("%s\n", str);
		lst = tokenization(str);
		if (!lst)
		{
			free(str);
			continue ;
		}
		print_lst(lst->next);
		ft_lstclear(&lst, del_t_token);
		free(str);
	}
	return (0);
}
