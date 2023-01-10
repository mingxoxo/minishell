/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:01:53 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/10 22:03:10 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include "return.h"
# include <stdlib.h>

# define T_SPACE 6

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_IO,
	T_PAREN,
	T_OPER
}	t_ttype;

typedef struct s_token
{
	t_ttype	type;
	char	*str;
}	t_token;

// token.c
t_error	tokenization(char *line);

// arr.c
int		*init_arr(size_t len);
void	fill_arr(char *line, int *arr);
void	handling_quote(char *line, int *arr, char c);

#endif