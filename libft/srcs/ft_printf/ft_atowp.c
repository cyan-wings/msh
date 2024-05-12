/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atowp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:23:34 by myeow             #+#    #+#             */
/*   Updated: 2024/04/11 21:12:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_atowp(const char **sptr)
{
	int		result;

	result = 0;
	while (**sptr && ft_in(BASE10, **sptr))
		result = result * 10 + *(*sptr)++ - '0';
	return ((int) result);
}
