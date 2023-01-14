/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env_second.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 23:09:53 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// substitute_env_second

static void	print_arr(int *arr, char *line)
{
	size_t	i;

	i = 0;
	printf("arr\n");
	while (i < ft_strlen(line))
	{
		printf(" %d", arr[i]);
		i++;
	}
	printf("\n");
}

static void	print_lst(t_list *lst)
{
	t_token	*token;

	printf("lst\n");
	while (lst)
	{
		token = (t_token *)(lst->content);
		printf("[%d] [%s]\n", token->type, token->str);
		lst = lst->next;
	}
	printf("\n");
}

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
	t_token	*token;

	clear_node(node->left, &del_t_token);
	del_t_token(node->content);
	node->content = NULL;
	node->left = NULL;
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
	if (node->content == NULL)
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (!token)
			return (ERROR);
		token->str = (char *)malloc(sizeof(char));
		token->str[0] = 0;
		token->type = T_WORD;
		node->content = token;
	}
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
	print_arr(arr, str);
	if (make_lst(str, arr, &lst) == ERROR)
	{
		free(arr);
		ft_lstclear(&lst, &del_t_token);
		return (ERROR);
	}
	print_lst(lst->next);
	free(arr);
	if (remake_cmd_tree(node, &lst) == ERROR)
		return (ERROR);
	return (SCS);
}
