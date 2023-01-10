/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:15:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/10 22:43:34 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "token.h"

static void	del_t_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)(content);
	if (token->str)
		free(token->str);
	free(content);
}

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

static t_error	make_token(char *line, t_ttype type, size_t len, t_list **lst)
{
	t_token	*token;
	t_list	*new;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (ERROR);
	token->str = (char *)malloc(sizeof(char) * (len + 1));
	new = ft_lstnew(token);
	if (!(token->str) || !new)
	{
		free(token->str);
		free(token);
		free(new);
		return (ERROR);
	}
	ft_strlcpy(token->str, line, len + 1);
	token->type = type;
	ft_lstadd_back(lst, new);
	return (SCS);
}

static size_t	count_len(char *line, int *arr, int i)
{
	size_t	len;

	i++;
	len = 1;
	while (line[i] && arr[i - 1] == arr[i])
	{
		len++;
		i++;
	}
	return (len);
}

static t_error	make_list(char *line, int *arr, t_list **lst)
{
	int		cust_idx;
	t_ttype	type;
	size_t	len;
	char	*start;

	start = line;
	while (*start)
	{
		cust_idx = arr[start - line];
		type = cust_idx / 10;
		if (type == T_SPACE)
		{
			start++;
			continue ;
		}
		if (type == T_WORD)
			len = count_len(line, arr, start - line);
		else
			len = cust_idx % 10 % 2 + 1;
		if (make_token(start, type, len, lst) == ERROR)
			return (ERROR);
		start += len;
	}
	return (SCS);
}

t_error	tokenization(char *line)
{
	int		*arr;
	t_list	*lst;

	arr = init_arr(ft_strlen(line));
	lst = ft_lstnew(NULL);
	if (!arr || !lst)
	{
		free(arr);
		free(lst);
		return (ERROR);
	}
	fill_arr(line, arr);
	handling_quote(line, arr, '\"');
	handling_quote(line, arr, '\'');
	if (make_list(line, arr, &lst) == ERROR)
	{
		free(arr);
		ft_lstclear(&lst, del_t_token);
		return (ERROR);
	}
	print_lst(lst->next);
	free(arr);
	ft_lstclear(&lst, del_t_token);
	return (SCS);
}
