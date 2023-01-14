/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:30:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/14 23:04:07 by jeongmin         ###   ########.fr       */
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
		{
			free(str);
			continue ;
		}
		add_history(str);
		lst = tokenization(str);
		if (!lst)
		{
			free(str);
			continue ;
		}
		print_lst(lst->next);
		if (!is_correct_syntax(lst->next))
		{
			ft_lstclear(&lst, del_t_token);
			free(str);
			continue ;
		}
		node = make_tree(lst->next);
		ft_lstclear(&lst, del_t_paren);
		preorder(node, 0, "root");
		subst_env(node);
		preorder(node, 0, "root");
		if (is_builtin_cmd(node))
			execute_builtin(node);
		else
			execute_cmds(node);
		clear_node(node, del_t_token);
		free(str);
		// system("leaks minishell | grep leaks");
	}
	clear_envp(&(g_var.envp));
	return (g_var.status);
}
