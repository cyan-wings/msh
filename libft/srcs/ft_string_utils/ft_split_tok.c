/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:27:59 by myeow             #+#    #+#             */
/*   Updated: 2024/05/17 18:17:15 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"
#include "ft_string_utils.h"

static int	ft_countwords(char *s, char const *set)
{
	size_t	w;

	w = 0;
	while (*s)
	{
		if (!*(s + 1) || ft_strchr(set, *s))
			++w;
		++s;
	}
	return (w);
}

/*
 * Modifies s. Hence, duplicate s if original copy is needed before calling
 * ft_split_tok.
 *
 * Free only needs to be done on the outer array.
 *
 * @param set: The set of delimiters to split.
 */
char	**ft_split_tok(char *s, char const *set)
{
	int		w;
	char	*token;
	char	**array;
	char	*saveptr;
	int		i;

	if (!s || !set)
		return (0);
	while (*s && ft_strchr(set, *s))
		++s;
	w = ft_countwords(s, set);
	array = (char **) ft_calloc(w + 1, sizeof(char *));
	if (!array)
		return (0);
	i = -1;
	token = ft_strtok_r(s, set, &saveptr);
	while (token)
	{
		array[++i] = token;
		token = ft_strtok_r(0, set, &saveptr);
	}
	return (array);
}
