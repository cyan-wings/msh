/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:46:12 by myeow             #+#    #+#             */
/*   Updated: 2024/06/30 21:41:06 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * while (env_list)
 *
 * printf("%s\n", ((t_env *) env_list->content)->val);
 * env_list = env_list->next;
 * }
 */
static void	minishell_init(t_list **env_list)
{
	minishell_load_history(HISTORY_FILE);
	minishell_env_init(env_list);
	return ;
}

static char	*minishell_get_input(t_list *env_list)
{
	char	*prompt;
	char	*input;

	prompt = minishell_prompt(env_list);
	input = readline(prompt);
	if (*input)
		minishell_save_history(input, HISTORY_FILE);
	printf("The input was: %s\n", input);
	ft_memdel((void **) &prompt);
	return (input);
}

static void	minishell_process_input(char *input)
{
	t_list	*token_list;

	token_list = 0;
	minishell_tokenise(input, &token_list);
	minishell_print_token_list(token_list);
	minishell_parse(token_list);
	minishell_tokenise_free(&token_list);
}

static void	minishell_clean(t_list **env_list)
{
	minishell_env_free(env_list);
}

int	main(void)
{
	char	*input;
	t_list	*env_list;

	input = 0;
	env_list = 0;
	minishell_init(&env_list);
	while (1)
	{
		input = minishell_get_input(env_list);
		minishell_process_input(input);
		free(input);
		break ;
	}
	minishell_clean(&env_list);
	//system("leaks minishell -q");
	return (0);
}
