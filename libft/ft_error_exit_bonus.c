/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:07:42 by wonyang           #+#    #+#             */
/*   Updated: 2022/12/04 14:15:30 by wonyang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	ft_error_exit(char *msg)
{
	if (write(2, msg, ft_strlen(msg)) == -1)
		ft_perror_exit("write error", 1);
	if (write(2, "\n", 1) == -1)
		ft_perror_exit("write error", 1);
	exit(1);
}
