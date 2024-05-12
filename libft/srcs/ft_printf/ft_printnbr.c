/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:13:06 by myeow             #+#    #+#             */
/*   Updated: 2024/04/11 21:37:22 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_print_sharp(t_data *data)
{
	char	s;

	s = data->flags.specifier;
	if (s == 'x')
		ft_appendstr_buffer(data, "0x", 2);
	else if (s == 'X')
		ft_appendstr_buffer(data, "0X", 2);
}

static void	check_print_sign(t_data *data, long long int n)
{
	if (n < 0)
		ft_appendchar_buffer(data, '-', 1);
	else if (data->flags.cross == 1)
		ft_appendchar_buffer(data, '+', 1);
	else if (data->flags.space == 1)
		ft_appendchar_buffer(data, ' ', 1);
	else if (data->flags.sharp == 1 && n)
		check_print_sharp(data);
}

static void	check_flag_zero(t_data *data, long long int n, int len)
{
	if (data->flags.zero && data->flags.precision == -1)
	{
		check_print_sign(data, n);
		ft_appendchar_buffer(data, '0', len);
	}
	else
	{
		ft_appendchar_buffer(data, ' ', len);
		check_print_sign(data, n);
	}
}

int	check_zero_int(t_data *data, long long int n)
{
	if (!n)
		return (!data->flags.precision);
	return (0);
}

int	ft_printnbr(t_data *data, long long int n, char *base, int base_len)
{
	int	w;
	int	p;
	int	nlen;

	w = data->flags.width - (data->flags.sharp * 2) - \
		((n < 0) || data->flags.cross || data->flags.space);
	p = data->flags.precision;
	nlen = ft_nbrlen_base(n, base_len) * !check_zero_int(data, n);
	p = nlen + ((p >= nlen) * (p - nlen));
	if (data->flags.hyphen)
	{
		check_print_sign(data, n);
		ft_appendchar_buffer(data, '0', p - nlen);
		ft_appendnbr_buffer(data, n, base, base_len);
		ft_appendchar_buffer(data, ' ', w - p);
	}
	else
	{
		check_flag_zero(data, n, w - p);
		ft_appendchar_buffer(data, '0', p - nlen);
		ft_appendnbr_buffer(data, n, base, base_len);
	}
	return (OK);
}
