/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:35:48 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/15 11:45:51 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include "return.h"
# include "ds_envp.h"

typedef struct s_global
{
	t_envp			envp;
	struct termios	old_term;
	struct termios	new_term;
	int				status;
}	t_global;

void	set_signal_handling(void);
void	set_minishell_setting(void);

#endif