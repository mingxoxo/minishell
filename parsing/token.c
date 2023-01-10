/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:15:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/10 21:57:19 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "token.h"

static void	print_arr(int *arr, char *line)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		printf(" %d", arr[i]);
		i++;
	}
	printf("\n");
}

// if space -> space가 끝날때까지
// if word -> word가 끝날때까지
// if oper -> oper 크기에 맞게 움직이기....!

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
	if (!(token->str))
	{
		free(token);
		return (ERROR);
	}
	new = ft_lstnew(token);
	if (!new)
	{
		free(token->str);
		free(token);
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
		if (type == T_SPACE || type == T_WORD)
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
	if (!arr)
		return (ERROR);
	lst = ft_lstnew(NULL);
	if (!lst)
		return (ERROR);
	fill_arr(line, arr);
	print_arr(arr, line);
	handling_quote(line, arr, '\"');
	handling_quote(line, arr, '\'');
	print_arr(arr, line);
	if (make_list(line, arr, &lst) == ERROR)
	{
		free(arr);
		ft_lstclear(&lst, free); // del 함수 수정하기
		return (ERROR);
	}
	print_lst(lst->next);
	free(arr);
	return (SCS);
}
