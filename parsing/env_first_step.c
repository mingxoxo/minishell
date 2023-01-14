/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_first_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:41:40 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 18:12:44 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"
#include "minishell.h"

static void	print_arr(int *arr, char *line)
{
	size_t	i;

	i = 0;
	printf("---------------print_arr-------------\n");
	while (i < ft_strlen(line))
	{
		printf(" %d", arr[i]);
		i++;
	}
	printf("-------------------------------------\n");
}

static void	print_lst(t_list *lst)
{
	t_token	*token;

	printf("---------------print_lst-------------\n");
	while (lst)
	{
		token = (t_token *)(lst->content);
		printf("[%d] [%s]\n", token->type, token->str);
		lst = lst->next;
	}
	printf("-------------------------------------\n");
}

static t_error	strjoin_list(t_list *lst, t_token *token)
{
	char	*new;
	char	*cache;

	cache = ft_strdup("");
	if (!cache)
		return (ERROR);
	while (lst)
	{
		new = ft_strjoin(cache, ((t_token *)(lst->content))->str);
		free(cache);
		if (!new)
			return (ERROR);
		cache = new;
		lst = lst->next;
	}
	free(token->str);
	token->str = cache;
	return (SCS);
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

static t_error	make_list(char *line, int *arr, t_list **lst)
{
	int		cust_idx;
	size_t	len;
	char	*start;

	start = line;
	while (*start)
	{
		cust_idx = arr[start - line];
		if (cust_idx == T_DOLLER * 10 + 1)
		{
			start++;
			continue ;
		}
		if (cust_idx == T_ENVP * 10 || cust_idx == T_WORD)
			len = count_len(line, arr, start - line);
		else
			len = cust_idx % 10 % 2 + 1;
		if (make_token(start, cust_idx / 10, len, lst) == ERROR)
			return (ERROR);
		start += len;
	}
	return (SCS);
}

static void	env_handling_quote(char *line, int *arr)
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
	print_arr(arr, token->str);
	env_handling_quote(token->str, arr);
	if (make_list(token->str, arr, &lst) == ERROR)
	{
		free(arr);
		ft_lstclear(&lst, &del_t_token);
		return (ERROR);
	}
	free(arr);
	print_lst(lst->next);
	subst_env_lst(lst->next);
	if (strjoin_list(lst->next, token))
	{
		ft_lstclear(&lst, del_t_token);
		return (ERROR);
	}
	printf("%s\n", token->str);
	ft_lstclear(&lst, del_t_token);
	return (SCS);
}
