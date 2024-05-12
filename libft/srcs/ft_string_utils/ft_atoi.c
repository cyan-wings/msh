/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 20:32:14 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:14:13 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char_utils.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned int		result;

	while (*str && ft_isspace(*str))
		++str;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1;
	}
	result = 0;
	while (*str && ft_isdigit(*str))
		result = result * 10 + *str++ - '0';
	return ((int)(result * sign));
}
