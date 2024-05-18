/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:31:32 by myeow             #+#    #+#             */
/*   Updated: 2024/05/17 14:42:20 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_mem_utils.h"

size_t	ft_strlen(const char *s);

char	*ft_strdup(const char *s1)
{
	void	*ptr;
	size_t	s1len;

	s1len = ft_strlen(s1);
	ptr = 0;
	ptr = malloc(s1len + 1);
	if (!ptr)
		return (0);
	return ((char *) ft_memmove(ptr, s1, s1len + 1));
}
