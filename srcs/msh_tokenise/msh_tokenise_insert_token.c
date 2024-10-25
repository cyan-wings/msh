/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tokenise_insert_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:00:08 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 15:47:16 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_tokenise.h"

t_token	*msh_tokenise_create_token(char *str);

#define META_C "<>|&()"
#define META_DOUBLE "<>|&"

/*
 * The string is guaranteed to have a closing quote.
 */
static int	get_close_quote_idx(char *str, int i, char quote_type)
{
	++i;
	while (str[i] && str[i] != quote_type)
		++i;
	return (i);
}

int	check_double_meta(char c1, char c2)
{
	if (!c2)
		return (0);
	if (c1 == c2 && ft_strchr(META_DOUBLE, c1))
		return (1);
	return (0);
}

/*
 * end character is inclusive.
 */
static char	*ft_strdup_start_end(char *str, int start, int end)
{
	char	*new_str;

	new_str = NULL;
	new_str = msh_utils_memalloc(end - start + 2,
			"msh_tokenise_insert_token", "ft_strdup_start_end");
	return ((char *) ft_memmove(new_str, str + start, end - start + 1));
}

void	msh_tokenise_insert_token(char *str, t_list **token_list)
{
	char	*token_val;
	int		i;
	int		start_token_i;

	token_val = NULL;
	i = -1;
	start_token_i = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = get_close_quote_idx(str, i, str[i]);
		if (ft_strchr(META_C, str[i]) || \
				ft_strchr(META_C, str[i + 1]) || !str[i + 1])
		{
			if (check_double_meta(str[i], str[i + 1]))
				++i;
			token_val = ft_strdup_start_end(str, start_token_i, i);
			ft_lstadd_back(token_list,
				ft_lstnew(msh_tokenise_create_token(token_val)));
			start_token_i = i + 1;
		}
	}
}
