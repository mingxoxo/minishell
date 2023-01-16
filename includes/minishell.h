/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:35:48 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/16 20:01:28 by wonyang          ###   ########seoul.kr  */
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
	int				is_signal;
}	t_global;

// signal.c
void	sigint_handler_prompt(int signo);
void	sigint_handler_parent(int signo);
void	sigint_handler_heredoc(int signo);

// terminal.c
t_error	init_minishell_setting(char **env);

// parse.c
t_tnode	*parse_line(char *str);

// main.c
void	run_code(char *str);

#endif