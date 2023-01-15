/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:35:48 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/15 19:07:01 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include "return.h"
# include "ds_envp.h"
# include "ds_tree.h"

# define PROMPT "\033[0;36mCUTE-Shell$\033[0m "

typedef struct s_global
{
	t_envp			envp;
	struct termios	old_term;
	struct termios	new_term;
	int				status;
}	t_global;

void	set_signal_handling(void);
void	set_minishell_setting(void);
t_tnode	*parse_line(char *str);

#endif