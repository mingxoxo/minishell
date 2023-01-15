/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:13:30 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/15 19:07:16 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

static void	del_quote_str(char *new, char *line, int *arr, size_t len)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (i < len)
	{
		if (arr[i] == T_QUOTE)
		{
			i++;
			continue ;
		}
		ft_strlcat(new, line + i, cnt + 2);
		cnt++;
		i++;
	}
}

static size_t	handling_del_quote(char *line, int *arr)
{
	size_t	len;
	char	*start;
	char	*end;

	len = 0;
	start = line;
	while (*start)
	{
		if (*start == '\"' || *start == '\'')
		{
			end = ft_strchr(start + 1, *start);
			if (!end)
				arr[start - line] = T_WORD;
			else
			{
				arr[start - line] = T_QUOTE;
				arr[end - line] = T_QUOTE;
				make_word_arr(arr, start - line + 1, end - line - 1);
				start = end;
				len += 2;
			}
		}
		start++;
	}
	return (len);
}

static t_error	del_quote_token(t_token *token)
{
	size_t	len;
	size_t	del;
	int		*arr;
	char	*new;

	len = ft_strlen(token->str);
	arr = init_arr(len);
	if (!arr)
		return (ERROR);
	del = handling_del_quote(token->str, arr);
	new = ft_calloc(len - del + 1, sizeof(char));
	if (!new)
	{
		free(arr);
		return (ERROR);
	}
	del_quote_str(new, token->str, arr, len);
	free(token->str);
	token->str = new;
	free(arr);
	return (SCS);
}

t_error	del_quote(t_tnode *node)
{
	t_error	errno;

	if (!node)
		return (SCS);
	errno = del_quote(node->left);
	errno = del_quote(node->right);
	if (is_this_symbol(node->content, T_WORD))
		return (del_quote_token(node->content));
	return (errno);
}
