/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:42:22 by myeow             #+#    #+#             */
/*   Updated: 2024/04/11 21:12:48 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parse_flags(t_data *data, const char **sptr)
{
	unsigned char	flag;

	while (ft_in(FLAGS, **sptr))
	{
		flag = *(*sptr)++;
		if (flag == '-')
			data->flags.hyphen = 1;
		else if (flag == '0')
			data->flags.zero = 1;
		else if (flag == '#')
			data->flags.sharp = 1;
		else if (flag == ' ')
			data->flags.space = 1;
		else if (flag == '+')
			data->flags.cross = 1;
	}
	return (OK);
}

static int	ft_get_pw(t_data *data, int *value, const char **sptr)
{
	if (**sptr == '*')
	{
		*value = va_arg(*data->args, int);
		++*sptr;
	}
	else
		*value = ft_atowp(sptr);
	return (*value);
}

static int	ft_check_undefined(t_data *data)
{
	char	s;

	s = data->flags.specifier;
	if (((s == 'x' || s == 'X') && data->flags.sharp) || s == 'u')
	{
		data->flags.space = 0;
		data->flags.cross = 0;
		return (UNDEFINED_ERROR);
	}
	return (OK);
}

int	ft_format(t_data *data, const char **sptr)
{
	int	e;

	e = 0;
	ft_bzero(&data->flags, sizeof(t_flags));
	data->flags.precision = -1;
	e += ft_parse_flags(data, sptr);
	ft_get_pw(data, &data->flags.width, sptr);
	if (data->flags.width < 0)
	{
		data->flags.hyphen = 1;
		data->flags.width = -data->flags.width;
	}
	if (**sptr == '.' && *++*sptr && \
			ft_get_pw(data, &data->flags.precision, sptr) < 0)
		data->flags.precision = -1;
	if (!ft_in(SPECIFIERS, **sptr) && **sptr != '%')
		return (PARSE_ERROR);
	data->flags.specifier = **sptr;
	if (data->flags.specifier == 'p')
		ft_format_addr(data);
	e += ft_check_undefined(data);
	return (e);
}

void	ft_format_specifier(t_data *data)
{
	char	specifier;

	specifier = data->flags.specifier;
	if (specifier == '%')
		ft_printchar(data, '%');
	else if (specifier == 'c')
		ft_printchar(data, va_arg(*data->args, int));
	else if (specifier == 's')
		ft_printstring(data, va_arg(*data->args, char *));
	else if (specifier == 'p')
		ft_printaddr(data, (uintptr_t) va_arg(*data->args, void *), BASE16);
	else if (specifier == 'd' || specifier == 'i')
		ft_printnbr(data, va_arg(*data->args, int), BASE10, 10);
	else if (specifier == 'u')
		ft_printnbr(data, va_arg(*data->args, unsigned int), BASE10, 10);
	else if (specifier == 'x')
		ft_printnbr(data, va_arg(*data->args, unsigned int), BASE16, 16);
	else if (specifier == 'X')
		ft_printnbr(data, va_arg(*data->args, unsigned int), BASE16CAPS, 16);
	return ;
}
