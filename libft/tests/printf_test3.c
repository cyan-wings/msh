/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:11:42 by myeow             #+#    #+#             */
/*   Updated: 2024/03/14 14:46:48 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	char	c;
	char	*str;
	int		max;
	int		min;
	int		zero;
	int		ten;
	int		negten;
	int		nine;
	int		negnine;
	int		one;
	int		negone;
	void	*ptr;
	char	*null_s;

	c = 65;
	str = "Sahni";
	max = 2147483647;
	min = -2147483648;
	zero = 0;
	ten = 10;
	negten = -10;
	nine = 9;
	negnine = -9;
	one = 1;
	negone = -1;
	ptr = (void *) "qerweiury";
	null_s = 0;
	ft_printf("\n\n");
	ft_printf("This is the beginning\n[%cc]\n[%sc]\n[%w]\nsahniisnoob\n", c, str);
	ft_printf("Percent: [%%]percent\n[%i]\n[%i]\n[%d]\n[%d]\n[%i]\n[%i]\n[%d]\n[%d]\n[%i]\n[%d]\n[%i]\n", \
			max, min, max, min, zero, ten, negten, nine, negnine, one, negone);
	ft_printf("%p\n", ptr);
	ft_printf("%x, %X, %x, %X, %x, %X, %x, %X, %x, %X, %x, %X\n", \
			max, min, max, min, zero, ten, negten, nine, negnine, one, negone, (unsigned int) ptr);
	ft_printf("[%s]\n", null_s);
	ft_printf(" [%p], [%p] \n", (void *) LONG_MIN, (void *) LONG_MAX);
	ft_printf(" [%p], [%p] \n", (void *) ULONG_MAX, (void *) -ULONG_MAX);
	printf("\n\n");
	printf("This is the beginning\n[%cc]\n[%sc]\n[w]\nsahniisnoob\n", c, str);
	printf("Percent: [%%]percent\n[%i]\n[%i]\n[%d]\n[%d]\n[%i]\n[%i]\n[%d]\n[%d]\n[%i]\n[%d]\n[%i]\n", \
			max, min, max, min, zero, ten, negten, nine, negnine, one, negone);
	printf("%p\n", ptr);
	printf("%x, %X, %x, %X, %x, %X, %x, %X, %x, %X, %x, %X\n", \
			max, min, max, min, zero, ten, negten, nine, negnine, one, negone, (unsigned int) ptr);
	printf("[%s]\n", null_s);
	printf(" [%p], [%p] \n", (void *) LONG_MIN, (void *) LONG_MAX);
	printf(" [%p], [%p] \n", (void *) ULONG_MAX, (void *) -ULONG_MAX);

	printf("%d\n", printf(" NULL [%s] NULL \n", NULL));printf("%d\n", ft_printf(" NULL [%s] NULL \n", NULL));
	printf(" [%x] \n", UINT_MAX);ft_printf(" [%x] \n", UINT_MAX);
	printf(" [%x] \n", UINT_MAX-1);ft_printf(" [%x] \n", UINT_MAX-1);
	printf(" [%x] \n", -1);ft_printf(" [%x] \n", -1);
	printf(" [%x] \n", 1);ft_printf(" [%x] \n", 1);
	printf(" [%x] \n", 0);ft_printf(" [%x] \n", 0);
	printf(" [%x] \n", INT_MIN);ft_printf(" [%x] \n", INT_MIN);
	printf(" [%x] \n", INT_MAX);ft_printf(" [%x] \n", INT_MAX);

	printf(" [%p] \n", (void * ) UINT_MAX);ft_printf(" [%p] \n", (void * ) UINT_MAX);
	printf(" [%p] \n", (void * ) UINT_MAX-1);ft_printf(" [%p] \n", (void * ) UINT_MAX-1);
	printf(" [%p] \n", (void * ) -1);ft_printf(" [%p] \n", (void * ) -1);
	printf(" [%p] \n", (void * ) 1);ft_printf(" [%p] \n", (void * ) 1);
	printf(" [%p] \n", (void * ) 0);ft_printf(" [%p] \n", (void * ) 0);
	printf(" [%p] \n", (void * ) INT_MIN);ft_printf(" [%p] \n", (void * ) INT_MIN);
	printf(" [%p] \n", (void * ) INT_MAX);ft_printf(" [%p] \n", (void * ) INT_MAX);
;
	return (0);
}
