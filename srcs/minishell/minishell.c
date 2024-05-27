/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:08:41 by myeow             #+#    #+#             */
/*   Updated: 2024/05/27 23:09:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
	return (0);
}*/

int	main(void)
{
	t_list	*env_list;

	env_list = 0;
	minishell_env_init(&env_list);
	while (env_list)
	{
		printf("%s\n", ((t_env *) env_list->content)->val);
		env_list = env_list->next;
	}
	minishell_env_free(&env_list);
	return (0);
}
