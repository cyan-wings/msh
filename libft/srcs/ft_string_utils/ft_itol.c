/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:57:52 by myeow             #+#    #+#             */
/*   Updated: 2024/07/06 13:58:53 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_i_strlen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		++len;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char	*ft_itol(long n)
{
	int				len;
	char			*s;
	unsigned long	nbr;

	len = ft_i_strlen(n);
	s = (char *) malloc(sizeof(char) * len + 1);
	if (!s)
		return (0);
	s[len] = 0;
	if (!n)
		s[0] = '0';
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	while (nbr)
	{
		s[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		s[--len] = '-';
	return (s);
}
