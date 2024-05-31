/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenise.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:50:38 by myeow             #+#    #+#             */
/*   Updated: 2024/05/31 13:06:14 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SYMBOLS "<>|&()"
#define WHITESPACES " \t\r\n\v\f"

#include "minishell.h"

static t_token	*create_token(char *word)
{
	t_token	*token;

	token = (t_token *) ft_memalloc(sizeof(t_token));
	if (!token)
		minishell_perror_exit("Token no mem", EXIT_FAILURE);
	token->string = word;
	return (token);
}

/*
 * end character is inclusive.
 */
static char	*ft_strdup_start_end(char *str, int start, int end)
{
	char	*new_str;

	new_str = 0;
	new_str = ft_memalloc(end - start + 2);
	return ((char *) ft_memmove(new_str, str + start, end - start + 1));
}

void	minishell_tokenise_insert(char *word, t_list **token_list)
{
	char	*token_string;
	int		i;
	int		start_token_i;

	token_string = 0;
	i = -1;
	start_token_i = 0;
	while (word[++i])
	{
		if (ft_strchr(SYMBOLS, word[i]) || ft_strchr(SYMBOLS, word[i + 1]) || !word[i + 1])
		{
			token_string = ft_strdup_start_end(word, start_token_i, i);
			ft_lstadd_back(token_list, ft_lstnew(create_token(token_string)));
			start_token_i = i + 1;
		}
	}
}

void	minishell_tokenise(char *input, t_list **token_list)
{
	const char	*delims = WHITESPACES;
	char		*word;
	char		*saveptr;

	if (!input || !token_list)
		return ;
	word = ft_strtok_r(input, delims, &saveptr);
	while (word)
	{
		minishell_tokenise_insert(word, token_list);
		word = ft_strtok_r(0, delims, &saveptr);
	}
	return ;
}
