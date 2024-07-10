/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnappend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:13:22 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 15:34:36 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strnappend(size_t n, char **strptr, ...)
{
	size_t	retsize;
	va_list	argv;

	if (!n)
		return (0);
	va_start(argv, atrptr);
	while (n--)
		ft_strappend(strptr, va_arg(argv, char *));
	va_end(argv);
}
