/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:22:10 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:14:42 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*ptr;

	ch = c;
	ptr = 0;
	--s;
	while (*++s)
		if (*s == ch)
			ptr = (char *) s;
	if (!c)
		return ((char *) s);
	return (ptr);
}
