/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/13 23:31:42 by wonyang          ###   ########seoul.kr  */
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

t_global	g_var;

static void	del_t_paren(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)(content);
	if (!is_this_symbol(token, T_PAREN))
		return ;
	if (token->str)
		free(token->str);
	free(content);
	content = NULL;
}

void	print_lst(t_list *lst)
{
	t_token	*token;

	printf("---------\n");
	while (lst)
	{
		token = (t_token *)(lst->content);
		printf("[%d] [%s]\n", token->type, token->str);
		lst = lst->next;
	}
	printf("---------\n");
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_tnode	*node;
	t_list	*lst;

	(void)argc;
	(void)argv;
	init_envp(&(g_var.envp), env);
	set_minishell_setting();
	lst = NULL;
	while (1)
	{
		str = readline("\033[0;36mCUTE-Shell$\033[0m ");
		if (str == NULL)
			break ;
		else if (ft_strcmp(str, "") == 0)
			continue ;
		add_history(str);
		lst = tokenization(str);
		if (!lst)
		{
			free(str);
			continue ;
		}
		if (!is_correct_syntax(lst->next))
		{
			ft_lstclear(&lst, del_t_token);
			free(str);
			continue ;
		}
		node = make_tree(lst->next);
		if (is_builtin_cmd(node))
			execute_builtin(node);
		else
			execute_cmds(node);
		ft_lstclear(&lst, del_t_paren);
		clear_node(node, del_t_token);
		free(str);
		system("leaks minishell");
	}
	clear_envp(&(g_var.envp));
	return (g_var.status);
}
