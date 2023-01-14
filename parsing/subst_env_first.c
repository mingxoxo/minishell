/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst_env_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:37 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 18:43:42 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"
#include "minishell.h"

// substitute_env_first

static void	handling_envp(int *arr, int len)
{
	int	i;

	i = 1;
	while (i < len)
	{
		if (arr[i] == T_WORD && arr[i - 1] / 10 == T_DOLLER)
		{
			arr[i - 1] = T_DOLLER * 10 + 1;
			arr[i] = T_ENVP * 10;
		}
		else if (arr[i] == T_WORD && arr[i - 1] == T_ENVP * 10)
			arr[i] = T_ENVP * 10;
		i++;
	}
	i = 0;
	while (i < len)
	{
		if (arr[i] == T_DOLLER * 10)
			arr[i] = 0;
		i++;
	}
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
				if (*start == '\'')
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
	const char	symbol[5][3] = {"\"", "\'", "$?", "$", " "};
	const int	cust_idx[] = {50, 52, 81, 70, 60};

	i = 0;
	while (i < 5)
	{
		if (ft_strncmp(line, (char *)(symbol[i]), ft_strlen(symbol[i])) == 0)
			return (cust_idx[i]);
		i++;
	}
	return (0);
}

t_error	env_first_step(t_token *token)
{
	int		*arr;
	t_list	*lst;

	arr = init_arr(ft_strlen(token->str));
	lst = ft_lstnew(NULL);
	if (!arr || !lst)
	{
		free(arr);
		free(lst);
		return (ERROR);
	}
	fill_arr(token->str, arr, &check_cust_idx);
	handling_envp(arr, ft_strlen(token->str));
	handling_quote_env(token->str, arr);
	if (subst_env_lst(token, arr, &lst) == ERROR)
	{
		free(arr);
		ft_lstclear(&lst, &del_t_token);
		return (ERROR);
	}
	printf("%s\n", token->str);
	free(arr);
	ft_lstclear(&lst, del_t_token);
	return (SCS);
}
