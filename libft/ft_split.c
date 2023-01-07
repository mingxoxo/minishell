/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:36:14 by wonyang           #+#    #+#             */
/*   Updated: 2022/12/04 13:14:25 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_all(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static char	**count_word(const char *str, char c)
{
	int		i;
	int		count;
	char	**result;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	result = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!result)
		return (result);
	return (result);
}

static int	skip_split(const char *str, char c, int n)
{
	int	i;

	i = n;
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

static int	input_value(const char *s, int *arr, char **result, char c)
{
	while (s[arr[1]])
	{
		if (s[arr[1]] == c)
		{
			result[arr[2]] = ft_substr(s, arr[0], arr[1] - arr[0]);
			if (!result[arr[2]])
			{
				free_all(result);
				return (1);
			}
			arr[2]++;
			arr[1] = skip_split(s, c, arr[1]);
			arr[0] = arr[1];
			continue ;
		}
		arr[1]++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		arr[3];

	result = count_word(s, c);
	if (!result)
		return (result);
	arr[1] = skip_split(s, c, 0);
	arr[0] = arr[1];
	arr[2] = 0;
	if (input_value(s, arr, result, c))
		return (0);
	if (s[arr[0]] != '\0')
	{
		result[arr[2]] = ft_substr(s, arr[0], arr[1] - arr[0]);
		if (!result[arr[2]])
		{
			free_all(result);
			return (0);
		}
	}
	return (result);
}
