/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/16 15:47:36 by wonyang          ###   ########seoul.kr  */
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

void	sigint_handler_prompt(int signo)
{
	(void)signo;
	g_var.status = 1;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_parent(int signo)
{
	(void)signo;
	g_var.status = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}

static t_error	set_envp_value(t_envp *envp)
{
	char	*str;
	int		num;

	str = getcwd(NULL, 0);
	if (!str)
		return (ERROR);
	set_env(envp, "PWD", str);
	free(str);
	del_key_enode(envp, "OLDPWD");
	set_env(envp, "OLDPWD", NULL);
	str = search_key_value(envp, "SHLVL");
	if (!str)
		set_env(envp, "SHLVL", "1");
	else
	{
		num = ft_atoi(str);
		str = ft_itoa(num + 1);
		if (!str)
			return (ERROR);
		set_env(envp, "SHLVL", str);
		free(str);
	}
	return (SCS);
}

t_error	init_minishell_setting(char **env)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, sigint_handler_prompt) == SIG_ERR
		|| init_envp(&(g_var.envp), env) == ERROR
		|| set_envp_value(&(g_var.envp)) == ERROR)
		return (ERROR);
	get_terminal_setting();
	g_var.status = 0;
	return (SCS);
}
