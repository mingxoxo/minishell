/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/15 11:49:27 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "minishell.h"

extern t_global	g_var;

static void	get_terminal_setting(void)
{
	tcgetattr(STDIN_FILENO, &(g_var.old_term));
	tcgetattr(STDIN_FILENO, &(g_var.new_term));
	g_var.new_term.c_lflag &= ~ECHOCTL;
	g_var.new_term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_var.new_term));
}

static void	sigint_handler_prompt(int signo)
{
	(void)signo;
	g_var.status = 1;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal_handling(void)
{
	signal(SIGINT, sigint_handler_prompt);
}

void	set_minishell_setting(void)
{
	get_terminal_setting();
	set_signal_handling();
	g_var.status = 0;
}
