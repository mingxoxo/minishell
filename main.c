/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/12 16:41:34 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "ds_envp.h"
#include "builtin.h"
#include "make_tree.h"
#include "minishell.h"
#include "execute.h"

t_envp	g_envp;

void	print_lst(t_list *lst)
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
	t_tnode	*node;
	t_list	*lst;

	(void)argc;
	(void)argv;
	init_envp(&g_envp, env);
	set_minishell_setting();
	lst = NULL;
	while (1)
	{
		str = readline("prompt$ ");
		if (str == NULL || ft_strcmp(str, "exit") == 0)
			exit(0);
		else if (ft_strcmp(str, "") == 0)
			continue ;
		add_history(str);
		// printf("%s\n", str);
		lst = tokenization(str);
		if (!lst)
		{
			free(str);
			continue ;
		}
		node = make_tree(lst->next);
		execute_cmds(node);
		clear_node(node, NULL);
		ft_lstclear(&lst, del_t_token);
		free(str);
	}
	clear_envp(&g_envp);
	return (0);
}
