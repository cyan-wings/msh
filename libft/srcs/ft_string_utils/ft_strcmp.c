/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:06:14 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:11:35 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	result;

	result = 0;
	while (*s1)
	{
		if (*s1 != *s2)
		{
			result = (unsigned char) *s1 - (unsigned char) *s2;
			return (result);
		}
		++s1;
		++s2;
	}
	if (*s1 != *s2)
	{
		result = (unsigned char) *s1 - (unsigned char) *s2;
		return (result);
	}
	return (result);
}
