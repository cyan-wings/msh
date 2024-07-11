/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:25:03 by myeow             #+#    #+#             */
/*   Updated: 2024/07/11 19:15:26 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char_utils.h"

long	ft_atol(const char *str)
{
	unsigned long	acc;
	int				sign;

	acc = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (*str && ft_isdigit(*str))
		acc = acc * 10 + *str++ - '0';
	return ((long)(acc * sign));
}
