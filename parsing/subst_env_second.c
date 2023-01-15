/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env_second.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/15 14:41:28 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// substitute_env_second

static void	handling_quote_env(char *line, int *arr)
{
	char	*start;
	char	*two;

	start = line;
	while (*start)
	{
		if (*start == '\"' || *start == '\'')
		{
			two = ft_strchr(start + 1, *start);
			if (!two)
				arr[start - line] = 0;
			else
			{
				make_word_arr(arr, start - line, two - line);
				start = two;
			}
		}
		start++;
	}
}

static int	check_cust_idx(char *line)
{
	int			i;
	const char	symbol[3][2] = {"\"", "\'", " "};
	const int	cust_idx[] = {50, 52, 60};

	i = 0;
	while (i < 3)
	{
		if (ft_strncmp(line, (char *)(symbol[i]), ft_strlen(symbol[i])) == 0)
		{
			return (cust_idx[i]);
		}
		i++;
	}
	return (0);
}

static t_error	remake_cmd_tree(t_tnode *node, t_list **head)
{
	t_list	*lst;

	clear_node(node->left, &del_t_token);
	del_t_token(node->content);
	node->content = NULL;
	node->left = NULL;
	if ((*head)->next == NULL && make_token("", T_WORD, 0, head) == ERROR)
	{
		ft_lstclear(head, &del_t_token);
		return (ERROR);
	}
	lst = (*head)->next;
	while (lst)
	{
		if (make_cmd(&node, &lst) == ERROR)
		{
			ft_lstclear(head, &del_t_token);
			return (ERROR);
		}
		lst = lst->next;
	}
	ft_lstclear(head, NULL);
	return (SCS);
}

t_error	env_second_step(char *str, t_tnode *node)
{
	int		*arr;
	t_list	*lst;

	arr = init_arr(ft_strlen(str));
	lst = ft_lstnew(NULL);
	if (!arr || !lst)
	{
		free(arr);
		free(lst);
		return (ERROR);
	}
	fill_arr(str, arr, &check_cust_idx);
	handling_quote_env(str, arr);
	if (make_lst(str, arr, &lst) == ERROR)
	{
		free(arr);
		ft_lstclear(&lst, &del_t_token);
		return (ERROR);
	}
	free(arr);
	if (remake_cmd_tree(node, &lst) == ERROR)
		return (ERROR);
	return (SCS);
}
