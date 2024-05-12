/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:58:21 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:20:10 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_read(char *s1, char *s2)
{
	char	*str;
	char	*str_cpy;
	char	*s1_cpy;

	if (!s1 || !s2)
		return (0);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (0);
	str_cpy = str;
	s1_cpy = s1;
	while (*s1_cpy)
		*str++ = *s1_cpy++;
	free(s1);
	while (*s2)
		*str++ = *s2++;
	return (str_cpy);
}
