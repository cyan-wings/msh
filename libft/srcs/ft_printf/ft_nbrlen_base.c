/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:31:53 by myeow             #+#    #+#             */
/*   Updated: 2024/04/11 21:35:39 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_nbrlen_base(long long int n, int base_len)
{
	int	count;

	if (!n)
		return (1);
	count = 0;
	if (n < 0)
		n = -n;
	while (n)
	{
		++count;
		n /= base_len;
	}
	return (count);
}
