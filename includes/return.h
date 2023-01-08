/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongmin <jeongmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:52:39 by jeongmin          #+#    #+#             */
/*   Updated: 2023/01/08 15:57:11 by jeongmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RETURN_H
# define RETURN_H

typedef enum e_check{
	FAIL = -1,
	SCS
}	t_check;

typedef enum e_error{
	ERROR = -2,
	FAIL = -1,
	SCS
}	t_error;

#endif