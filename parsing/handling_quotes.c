/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:29:03 by  jeongmin         #+#    #+#             */
/*   Updated: 2023/01/13 22:41:56 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_tree.h"

// static t_error	word_subst_env(t_token *token)
// {
// 	int		i;
// 	char	*str;
// 	char	*new;

// 	i = 0;
// 	new = NULL;
// 	str = token->str;
// 	while (token->str[i])
// 	{
// 		if (token->str[i] == '\"' || token->str[i] == '\'')
// 			i += search_pair_quote(token->str, i);
// 		if (token->str[i] == '$')
// 		{
		
// 		}
// 		i++;
// 	}
// 	return (SCS);
// }

int	search_pair_quote(char *str, int idx)
{
	int		len;
	char	quote;

	len = 0;
	quote = str[idx];
	idx++;
	while (str[idx])
	{
		len++;
		if (str[idx] == quote)
			return (len);
		idx++;
	}
	return (len);
}
