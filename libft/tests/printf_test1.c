/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:46:10 by myeow             #+#    #+#             */
/*   Updated: 2024/03/14 16:46:01 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"
#include <stdio.h>

int	main(void)
{
	//char	c = 'h';
	//ft_printf_bonus("something[%.*c]something\n", -10, c);
	//printf("something[%.*c]something\n", -10, c);

	//char	*str = "Hello";
	//ft_printf_bonus("something[%*.*s]something\n", -6, -1, str);
	//printf("something[%*.*s]something\n", -6, -1, str);
	//
	//
	int i = 1234;

	ft_printf_bonus("some[%0*.*d]some", -20, -5, i);
	printf("some[%0*.*d]some\n", -20, -5, i);
	
		
	printf("[%0.3d]\n", -1234);ft_printf_bonus("[%0.3d]\n", -1234);
	printf("[%05.d]\n", -2);ft_printf_bonus("[%05.d]\n", -2);
	printf("[%5d]\n", -20);ft_printf_bonus("[%5d]\n", -20);
	printf("[%05.10d]\n", -211110);ft_printf_bonus("[%05.10d]\n", -211110);
	printf("[%10.5d]\n", -211110);ft_printf_bonus("[%10.5d]\n", -211110);
	printf("[%.5d]\n", 20);ft_printf_bonus("[%.5d]\n", 20);
	printf("[%-5d]\n", 20);ft_printf_bonus("[%-5d]\n", 20);
	printf("[%+05d]\n", -0);ft_printf_bonus("[%+05d]\n", -0);
	printf("[%+05d]\n", 2);ft_printf_bonus("[%+05d]\n", 2);
	printf("[%+0d]\n", 0);ft_printf_bonus("[%+0d]\n", 0);
	printf("[%+010.5d]\n", 20);ft_printf_bonus("[%+010.5d]\n", 20);
	printf("[%010.5d]\n", 20);ft_printf_bonus("[%010.5d]\n", 20);
	printf("[% d]\n", -20);ft_printf_bonus("[% d]\n", -20);
	printf("[%  d]\n", 20);ft_printf_bonus("[%  d]\n", 20);
	printf("%d\n", printf("[%+-*.*i]\n", 10, 7, 1234));printf("%d\n", ft_printf_bonus("[%+- 0*.*i]\n", 10, 7, 1234));
	
	printf("+++++++++++++++++++++++++++++\n");
	printf("[%05u]\n", 2);ft_printf_bonus("[%05u]\n", 2);
	printf("[%05.u]\n", 2);ft_printf_bonus("[%05.u]\n", 2);
	printf("[%5u]\n", 20);ft_printf_bonus("[%5u]\n", 20);
	printf("[%.12u]\n", -3);ft_printf_bonus("[%.12u]\n", -3);
	printf("[%10.5u]\n", 211110);ft_printf_bonus("[%10.5u]\n", 211110);
	printf("[%.5u]\n", 20);ft_printf_bonus("[%.5u]\n", 20);
	printf("[%-5u]\n", 20);ft_printf_bonus("[%-5u]\n", 20);
	printf("[%010.5u]\n", 20);ft_printf_bonus("[%010.5u]\n", 20);
	printf("-----------------------------\n");

	printf("+++++++++++++++++++++++++++++\n");
	printf("%d\n", printf("[%x]\n", 0));printf("%d\n", ft_printf_bonus("[%x]\n", 0));
	printf("%d\n", printf("[%5x]\n", 20));printf("%d\n", ft_printf_bonus("[%5x]\n", 20));
	printf("%d\n", printf("[%5.3x]\n", 20));printf("%d\n", ft_printf_bonus("[%5.3x]\n", 20));
	printf("%d\n", printf("[%5.7x]\n", 20));printf("%d\n", ft_printf_bonus("[%5.7x]\n", 20));
	printf("%d\n", printf("[%05.3x]\n", 20));printf("%d\n", ft_printf_bonus("[%05.3x]\n", 20));
	printf("%d\n", printf("[%-5x]\n", 20));printf("%d\n", ft_printf_bonus("[%-5x]\n", 20));
	printf("%d\n", printf("[%#5x]\n", 20));printf("%d\n", ft_printf_bonus("[%#5x]\n", 20));
	printf("%d\n", printf("[%05x]\n", 20));printf("%d\n", ft_printf_bonus("[%05x]\n", 20));
	printf("%d\n", printf("[%#05.3x]\n", 20));printf("%d\n", ft_printf_bonus("[%#05.3x]\n", 20));
	printf("%d\n", printf("[%#0*.*x]\n", 10, 7, 20));printf("%d\n", ft_printf_bonus("[%#0*.*x]\n", 10, 7, 20));
	printf("%d\n", printf("[%#5.3x]\n", 20));printf("%d\n", ft_printf_bonus("[%#5.3x]\n", 20));
	printf("%d\n", printf("[%#5.x]\n", 20));printf("%d\n", ft_printf_bonus("[%#5.x]\n", 20));
	printf("%d\n", printf("[%#20.7x]\n", -20000));printf("%d\n", ft_printf_bonus("[%# 20.7x]\n", -20000));
	printf("-----------------------------\n");

	printf("%d\n", printf(" NULL [%s] NULL \n", NULL));printf("%d\n", ft_printf_bonus(" NULL [%s] NULL \n", NULL));
	printf(" [%#x] \n", UINT_MAX);ft_printf_bonus(" [%#x] \n", UINT_MAX);
	printf(" [%#x] \n", UINT_MAX-1);ft_printf_bonus(" [%#x] \n", UINT_MAX-1);
	printf(" [%#x] \n", -1);ft_printf_bonus(" [%#x] \n", -1);
	printf(" [%#x] \n", 1);ft_printf_bonus(" [%#x] \n\n", 1);
	printf(" [%#x] \n", 0);ft_printf_bonus(" [%#x] \n", 0);
	printf(" [%#x] \n", INT_MIN);ft_printf_bonus(" [%#x] \n", INT_MIN);
	printf(" [%#x] \n", INT_MAX);ft_printf_bonus(" [%#x] \n", INT_MAX);

	printf(" [%p] \n", (void * ) UINT_MAX);ft_printf_bonus(" [%p] \n", (void * ) UINT_MAX);
	printf(" [%p] \n", (void * ) UINT_MAX-1);ft_printf_bonus(" [%p] \n", (void * ) UINT_MAX-1);
	printf(" [%p] \n", (void * ) -1);ft_printf_bonus(" [%p] \n", (void * ) -1);
	printf(" [%p] \n", (void * ) 1);ft_printf_bonus(" [%p] \n", (void * ) 1);
	printf(" [%p] \n", (void * ) 0);ft_printf_bonus(" [%p] \n", (void * ) 0);
	printf(" [%p] \n", (void * ) INT_MIN);ft_printf_bonus(" [%p] \n", (void * ) INT_MIN);
	printf(" [%p] \n", (void * ) INT_MAX);ft_printf_bonus(" [%p] \n", (void * ) INT_MAX);

	printf(" [%p], [%p] \n", (void *) LONG_MIN, (void *) LONG_MAX);ft_printf_bonus(" [%p], [%p] \n", (void *) LONG_MIN, (void *) LONG_MAX);
	printf(" [%p], [%p] \n", (void *) ULONG_MAX, (void *) -ULONG_MAX);ft_printf_bonus(" [%p], [%p] \n", (void *) ULONG_MAX, (void *) -ULONG_MAX);


	return(0);
}
