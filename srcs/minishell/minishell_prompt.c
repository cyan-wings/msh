/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:37:52 by myeow             #+#    #+#             */
/*   Updated: 2024/05/27 00:47:40 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "ft_mem_utils.h"
#include "ft_string_utils.h"

/*
 * Prompt must be freed.
 */
char	*minishell_prompt(void)
{
	char	buffer[1024];
	char	*prompt;
	int		i;

	if (!getcwd(buffer, 1024))
		minishell_perror_exit("getcwd", EXIT_FAILURE);
	prompt = ft_calloc(ft_strlen(buffer) + 3, sizeof(char));
	if (!prompt)
		minishell_perror_exit("Prompt memalloc", EXIT_FAILURE);
	i = -1;
	while (buffer[++i])
		prompt[i] = buffer[i];
	prompt[i++] = '$';
	prompt[i] = ' ';
	return (prompt);
}
