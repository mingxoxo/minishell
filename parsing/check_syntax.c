/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:52:16 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/17 13:38:17 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

static bool	is_correct_paren(t_list *lst, char **str)
{
	int	cnt;

	cnt = 0;
	*str = "invalid parenthesis pair";
	while (lst)
	{
		cnt += check_paren(lst->content);
		if (cnt < 0)
			return (false);
		lst = lst->next;
	}
	if (cnt != 0)
		return (false);
	return (true);
}

static bool	is_correct_io(t_list *lst, char **str)
{
	*str = "redirection file does not exist";
	while (lst)
	{
		if (is_this_symbol(lst->content, T_IO))
		{
			lst = lst->next;
			if (!lst || !is_this_symbol(lst->content, T_WORD))
				return (false);
		}
		lst = lst->next;
	}
	return (true);
}

static bool	is_paren_pos_ok(t_list *lst)
{
	t_list	*left;
	t_list	*right;

	left = NULL;
	while (lst)
	{
		if (check_paren(lst->content) == OPEN_PAREN)
		{
			right = lst->next;
			right = check_end_node(&right);
			if (!right)
				return (false);
			right = right->next->next;
			if ((!left || !is_dsv_symbol(left->content)) \
				&& (!right || !is_dsv_symbol(right->content)))
				return (false);
		}
		left = lst;
		lst = lst->next;
	}
	return (true);
}

static bool	is_cmd_pos_ok(t_list *lst, char	**str)
{
	int	flag;

	flag = 0;
	*str = "command not found";
	while (lst)
	{
		if (is_dsv_symbol(lst->content))
		{
			*str = ((t_token *)(lst->content))->str;
			if (flag != 1)
				return (false);
			flag = 0;
		}
		else if (is_this_symbol(lst->content, T_WORD) && flag == 0)
			flag = 1;
		else if (is_this_symbol(lst->content, T_IO))
			lst = lst->next;
		lst = lst->next;
	}
	if (flag != 1)
		return (false);
	return (true);
}

bool	is_correct_syntax(t_list *lst)
{
	char	*str;

	str = NULL;
	if (!is_correct_paren(lst, &str) || !is_correct_io(lst, &str))
	{
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putendl_fd(str, 2);
		return (false);
	}
	if (!is_paren_pos_ok(lst))
	{
		ft_putstr_fd("minishell: syntax error: ", 2);
		ft_putendl_fd("invalid parenthesis position", 2);
		return (false);
	}
	if (!is_cmd_pos_ok(lst, &str) && str)
	{
		ft_putstr_fd("minishell: syntax error: ", 2);
		ft_putendl_fd(str, 2);
		return (false);
	}
	return (true);
}
