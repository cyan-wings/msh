/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:52:12 by myeow             #+#    #+#             */
/*   Updated: 2024/04/11 21:37:40 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flush_buffer(t_data *data)
{
	data->count += write(1, data->buffer, data->buffer_idx);
	ft_bzero(data->buffer, BUFFER_SIZE);
	data->buffer_idx = 0;
}

void	ft_write_buffer(t_data *data, int c)
{
	if (data->buffer_idx == BUFFER_SIZE)
		ft_flush_buffer(data);
	data->buffer[data->buffer_idx++] = c;
}

void	ft_appendchar_buffer(t_data *data, int c, int n)
{
	if (n <= 0)
		return ;
	while (n--)
		ft_write_buffer(data, c);
}

void	ft_appendstr_buffer(t_data *data, const char *str, int n)
{
	if (n <= 0)
		return ;
	while (n-- && *str)
		ft_write_buffer(data, *str++);
}

void	ft_appendnbr_buffer(t_data *data, long long int n, \
		char *base, int base_len)
{
	if (check_zero_int(data, n))
		return ;
	if (n < 0)
		return (ft_appendnbr_buffer(data, -n, base, base_len));
	if (n < base_len)
		ft_appendchar_buffer(data, base[n], 1);
	else
	{
		ft_appendnbr_buffer(data, n / base_len, base, base_len);
		ft_appendchar_buffer(data, base[n % base_len], 1);
	}
}
