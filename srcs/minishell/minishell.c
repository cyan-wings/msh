/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:46:12 by myeow             #+#    #+#             */
/*   Updated: 2024/07/06 22:18:54 by myeow            ###   ########.fr       */
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
	t_ast	*root;
	int		flag;

	token_list = 0;
	root = 0;
	flag = 0;
	flag = minishell_tokenise(input, &token_list);
	if (!flag)
	{
		minishell_perror("Tokenise_error.");
		minishell_tokenise_free(&token_list);
		return ;
	}
	minishell_print_token_list(token_list);
	flag = minishell_parse(token_list, &root);
	if (!flag)
		minishell_perror("Parsing_error.");
	minishell_parse_astprint(root, 0);
	minishell_parse_astfree(&root);
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
	system("leaks minishell -q");
	return (0);
}
