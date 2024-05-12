/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:53:01 by myeow             #+#    #+#             */
/*   Updated: 2024/04/11 22:06:52 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format_addr(t_data *data)
{
	data->flags.sharp = 1;
	data->flags.space = 0;
	data->flags.cross = 0;
}

static void	ft_appendaddr_buffer(t_data *data, uintptr_t n, char *base)
{
	if (!n && !data->flags.precision)
		return ;
	if (n < 16)
		ft_appendchar_buffer(data, base[n], 1);
	else
	{
		ft_appendaddr_buffer(data, n / 16, base);
		ft_appendchar_buffer(data, base[n % 16], 1);
	}
}

static int	ft_addrlen(uintptr_t n)
{
	int	count;

	if (!n)
		return (1);
	count = 0;
	while (n)
	{
		++count;
		n /= 16;
	}
	return (count);
}

int	ft_printaddr(t_data *data, uintptr_t n, char *base)
{
	int	w;
	int	p;
	int	nlen;

	w = data->flags.width - 2;
	p = data->flags.precision;
	nlen = ft_addrlen(n) - (!data->flags.precision * ft_addrlen(n));
	p = nlen + ((p >= nlen) * (p - nlen));
	if (data->flags.hyphen)
	{
		ft_appendstr_buffer(data, "0x", 2);
		ft_appendchar_buffer(data, '0', p - nlen);
		ft_appendaddr_buffer(data, n, base);
		ft_appendchar_buffer(data, ' ', w - p);
	}
	else
	{
		ft_appendchar_buffer(data, ' ', w - p);
		ft_appendstr_buffer(data, "0x", 2);
		ft_appendchar_buffer(data, '0', p - nlen);
		ft_appendaddr_buffer(data, n, base);
	}
	return (OK);
}
