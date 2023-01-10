/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:32 by wonyang           #+#    #+#             */
/*   Updated: 2023/01/10 16:37:07 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>

void	get_terminal_setting(void)
{
	struct termios	old_term;
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &old_term);
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	new_term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}
