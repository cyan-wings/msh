/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:46:10 by myeow             #+#    #+#             */
/*   Updated: 2024/03/14 16:47:13 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

int	main()
{
	printf("[% .d]\n", 0);ft_printf_bonus("[% .d]\n", 0);
	printf("[%+.d]\n", 0);ft_printf_bonus("[%+.d]\n", 0);
	printf("[% 10.d]\n", 0);ft_printf_bonus("[% 10.d]\n", 0);
	printf("[%+10.d]\n", 0);ft_printf_bonus("[%+10.d]\n", 0);
	printf("[%- 10.d]\n", 0);ft_printf_bonus("[%- 10.d]\n", 0);
	printf("[%-+10.d]\n", 0);ft_printf_bonus("[%-+10.d]\n", 0);
	printf("[% 10.5d]\n", 0);ft_printf_bonus("[% 10.5d]\n", 0);
	printf("[%+10.5d]\n", 0);ft_printf_bonus("[%+10.5d]\n", 0);

	printf("[% .i]\n", 0);ft_printf_bonus("[% .i]\n", 0);
	printf("[%+.i]\n", 0);ft_printf_bonus("[%+.i]\n", 0);
	printf("[% 10.i]\n", 0);ft_printf_bonus("[% 10.i]\n", 0);
	printf("[%+10.i]\n", 0);ft_printf_bonus("[%+10.i]\n", 0);
	printf("[%- 10.i]\n", 0);ft_printf_bonus("[%- 10.i]\n", 0);
	printf("[%-+10.i]\n", 0);ft_printf_bonus("[%-+10.i]\n", 0);
	printf("[% 10.5i]\n", 0);ft_printf_bonus("[% 10.5i]\n", 0);
	printf("[%+10.5i]\n", 0);ft_printf_bonus("[%+10.5i]\n", 0);

	printf("[%.u]\n", 0);ft_printf_bonus("[% .u]\n", 0);
	printf("[%.u]\n", 0);ft_printf_bonus("[%+.u]\n", 0);
	printf("[%10.u]\n", 0);ft_printf_bonus("[% 10.u]\n", 0);
	printf("[%10.u]\n", 0);ft_printf_bonus("[%+10.u]\n", 0);
	printf("[%-10.u]\n", 0);ft_printf_bonus("[%- 10.u]\n", 0);
	printf("[%-10.u]\n", 0);ft_printf_bonus("[%-+10.u]\n", 0);
	printf("[%10.5u]\n", 0);ft_printf_bonus("[% 10.5u]\n", 0);
	printf("[%10.5u]\n", 0);ft_printf_bonus("[%+10.5u]\n", 0);
	printf("[%.u]\n", 0);ft_printf_bonus("[%.u]\n", 0);
	printf("[%.u]\n", 0);ft_printf_bonus("[%.u]\n", 0);
	printf("[%10.u]\n", 0);ft_printf_bonus("[%10.u]\n", 0);
	printf("[%10.u]\n", 0);ft_printf_bonus("[%10.u]\n", 0);
	printf("[%-10.u]\n", 0);ft_printf_bonus("[%-10.u]\n", 0);
	printf("[%-10.u]\n", 0);ft_printf_bonus("[%-10.u]\n", 0);
	printf("[%10.5u]\n", 0);ft_printf_bonus("[%10.5u]\n", 0);
	printf("[%10.5u]\n", 0);ft_printf_bonus("[%10.5u]\n", 0);

	char *c = 0;

	printf("[%.s]\n", c);ft_printf_bonus("[%.s]\n", c);
	printf("[%.s]\n", c);ft_printf_bonus("[%.s]\n", c);
	printf("[%10.s]\n", c);ft_printf_bonus("[%10.s]\n", c);
	printf("[%10.s]\n", c);ft_printf_bonus("[%10.s]\n", c);
	printf("[%-10.s]\n", c);ft_printf_bonus("[%-10.s]\n", c);
	printf("[%-10.s]\n", c);ft_printf_bonus("[%-10.s]\n", c);
	printf("[%10.5s]\n", c);ft_printf_bonus("[%10.5s]\n", c);
	printf("[%10.5s]\n", c);ft_printf_bonus("[%10.5s]\n", c);

	return (0);
}
