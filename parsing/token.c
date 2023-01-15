/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:15:15 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 23:07:37 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	del_t_token(void *content)
{
	t_token	*token;

	if (!content)
		return ;
	token = (t_token *)(content);
	if (token->str)
		free(token->str);
	free(content);
	content = NULL;
}

t_error	make_token(char *line, t_ttype type, size_t len, t_list **lst)
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

static int	check_cust_idx(char *line)
{
	int			i;
	const char	symbol[12][3] = {"\"", "\'", "&&", "||", "(", ")", \
								"<<", "<", ">>", ">", "|", " "};
	const int	cust_idx[] = {50, 52, 41, 43, 30, 32, \
								21, 22, 23, 24, 10, 60};

	i = 0;
	while (i < 12)
	{
		if (ft_strncmp(line, (char *)(symbol[i]), ft_strlen(symbol[i])) == 0)
			return (cust_idx[i]);
		i++;
	}
	return (0);
}

t_error	make_lst(char *line, int *arr, t_list **lst)
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

t_list	*tokenization(char *line)
{
	int		*arr;
	t_list	*lst;

	arr = init_arr(ft_strlen(line));
	lst = ft_lstnew(NULL);
	if (!arr || !lst)
	{
		free(arr);
		free(lst);
		return (NULL);
	}
	fill_arr(line, arr, &check_cust_idx);
	handling_quote(line, arr, '\"');
	handling_quote(line, arr, '\'');
	if (make_lst(line, arr, &lst) == ERROR)
	{
		free(arr);
		ft_lstclear(&lst, &del_t_token);
		return (NULL);
	}
	free(arr);
	return (lst);
}
