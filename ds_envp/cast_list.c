/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:21:17 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/08 17:24:37 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ds_envp.h"

static int	search_sep(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static t_error	get_key(char *line, char **key)
{
	int	sep;

	sep = search_sep(line);
	if (sep == -1)
		return (FAIL);
	*key = (char *)malloc(sizeof(char) * (sep + 1));
	if (!(*key))
		return (ERROR);
	ft_strlcpy(*key, line, sep + 1);
	return (SCS);
}

static t_error	get_value(char *line, char **value)
{
	int	sep;

	sep = search_sep(line);
	if (sep == -1)
		return (FAIL);
	*value = ft_strdup(line + sep + 1);
	if (!(*value))
		return (ERROR);
	return (SCS);
}

t_error	cast_envp_line(t_envp *envp, char *line)
{
	t_error	errno;
	char	*key;
	char	*value;

	errno = get_key(line, &key);
	if (errno != SCS)
		return (errno);
	errno = get_value(line, &value);
	if (errno != SCS)
		return (errno);
	if (set_key_value(envp, key, value) == ERROR)
		return (ERROR);
	return (SCS);
}

t_error	cast_envp_list(t_envp *envp, char **arr)
{
	t_error	errno;

	while (*arr)
	{
		errno = cast_envp_line(envp, *arr);
		if (errno != SCS)
			return (errno);
		arr++;
	}
	return (SCS);
}
