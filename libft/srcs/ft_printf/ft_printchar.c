/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:29:51 by myeow             #+#    #+#             */
/*   Updated: 2024/04/11 21:13:34 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_zero_percent(t_data *data, int w)
{
	if (data->flags.specifier == '%' && data->flags.zero == 1)
		ft_appendchar_buffer(data, '0', w);
	else
		ft_appendchar_buffer(data, ' ', w);
}

int	ft_printchar(t_data *data, int c)
{
	int	width;

	width = data->flags.width;
	if (data->flags.hyphen)
	{
		ft_appendchar_buffer(data, c, 1);
		ft_appendchar_buffer(data, ' ', --width);
	}
	else
	{
		check_zero_percent(data, --width);
		ft_appendchar_buffer(data, c, 1);
	}
	return (OK);
}
