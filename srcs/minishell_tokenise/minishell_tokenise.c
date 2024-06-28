/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenise.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:50:38 by myeow             #+#    #+#             */
/*   Updated: 2024/06/27 15:25:41 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define METACHARS "<>|&()"
#define WHITESPACES " \t\r\n\v\f"

/*
 * This function is to tokenise those double METACHARS.
 * If for example there are 3 of the same metachars (i.e., "<<<"),
 * it shall be tokenised as "<<" and "<". 
 * The incrementer is implemented in the minishell_tokenise function.
 */
static int	check_double_symbol(char c1, char c2)
{
	if (!c2)
		return (0);
	if (c1 == c2 && ft_strchr(METACHARS, c1))
		return (1);
	return (0);
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

static t_token	*create_token(char *word)
{
	t_token	*token;

	token = (t_token *) ft_memalloc(sizeof(t_token));
	if (!token)
		minishell_perror_exit("Token no mem", EXIT_FAILURE);
	token->value = word;
	return (token);
}

static void	minishell_tokenise_insert(char *word, t_list **token_list)
{
	char	*token_string;
	int		i;
	int		start_token_i;

	token_string = 0;
	i = -1;
	start_token_i = 0;
	while (word[++i])
	{
		if (ft_strchr(METACHARS, word[i]) || \
				ft_strchr(METACHARS, word[i + 1]) || !word[i + 1])
		{
			if (check_double_symbol(word[i], word[i + 1]))
				++i;
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
