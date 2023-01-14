/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:01:53 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/14 21:55:27 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include "return.h"
# include <stdlib.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_IO,
	T_PAREN,
	T_OPER,
	T_QUOTE,
	T_SPACE,
	T_DOLLER,
	T_ENVP
}	t_ttype;

typedef struct s_token
{
	t_ttype	type;
	char	*str;
}	t_token;

// token.c
void	del_t_token(void *content);
t_error	make_lst(char *line, int *arr, t_list **lst);
t_error	make_token(char *line, t_ttype type, size_t len, t_list **lst);
t_list	*tokenization(char *line);

// arr.c
int		*init_arr(size_t len);
void	fill_arr(char *line, int *arr, int (*chk_idx)(char *));
void	make_word_arr(int *arr, int start, int end);
size_t	count_len(char *line, int *arr, int i);
void	handling_quote(char *line, int *arr, char c);

#endif