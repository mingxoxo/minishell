/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:01:53 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/10 19:05:03 by jeongmin         ###   ########.fr       */
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
	T_SPACE,
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

t_error	tokenization(char *line);

#endif