/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:42:52 by myeow             #+#    #+#             */
/*   Updated: 2024/05/18 15:43:04 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"

size_t	ft_strlen(const char *s);

void	ft_strclr(char *s)
{
	if (!s)
		return ;
	return (ft_bzero(s, ft_strlen(s)));
}
