/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:08:41 by myeow             #+#    #+#             */
/*   Updated: 2024/05/27 00:43:49 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	extern char	**environ;

	while (environ && *environ)
		printf("%s\n", *environ++);
	return (0);
}
*/

#include <readline/readline.h>
#include <stdlib.h>
#include "minishell.h"
#include "ft_mem_utils.h"

int	main(void)
{
	char	*input;
	char	*prompt;

	minishell_load_history(HISTORY_FILE);
	input = "INITIAL PTR";
	prompt = 0;
	while (input)
	{
		prompt = minishell_prompt();
		input = readline(prompt);
		if (*input)
			minishell_save_history(input, HISTORY_FILE);
		printf("The input was: %s\n", input);
		free(input);
		ft_memdel((void **) &prompt);
	}
	return 0;
}
