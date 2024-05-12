/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:36:22 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:06:09 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print_utils.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s--)
		return ;
	while (*++s)
		ft_putchar_fd(*s, fd);
	ft_putchar_fd('\n', fd);
}
