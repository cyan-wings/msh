/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:36:59 by myeow             #+#    #+#             */
/*   Updated: 2024/07/17 17:26:45 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
 * while (env_list)
 *
 * printf("%s\n", ((t_env *) env_list->content)->val);
 * env_list = env_list->next;
 * }
 */
static void	msh_init(t_list **env_list)
{
	msh_load_history(HISTORY_FILE);
	msh_env_init(env_list);
	return ;
}

static char	*msh_get_input(t_list *env_list)
{
	char	*prompt;
	char	*input;

	prompt = msh_prompt(env_list);
	input = readline(prompt);
	if (*input)
		msh_save_history(input, HISTORY_FILE);
	printf("The input was: %s\n", input);
	ft_memdel((void **) &prompt);
	return (input);
}

static void	msh_process_input(char *input, t_list **env_list)
{
	t_list	*token_list;
	t_ast	*root;
	int		flag;

	token_list = 0;
	root = 0;
	flag = 0;
	flag = msh_tokenise(input, &token_list);
	if (!flag)
	{
		msh_perror("Tokenise_error.");
		msh_tokenise_free(&token_list);
		return ;
	}
	msh_print_token_list(token_list);
	flag = msh_parse(token_list, &root);
	if (!flag)
		msh_perror("Parsing_error.");
	msh_parse_astprint(root, 0);
	msh_expansion(root, *env_list);
	msh_env_array(*env_list);
	msh_parse_astfree(&root);
	msh_tokenise_free(&token_list);
}

static void	msh_clean(t_list **env_list)
{
	msh_env_free(env_list);
}

int	main(void)
{
	char	*input;
	t_list	*env_list;

	input = 0;
	env_list = 0;
	msh_init(&env_list);
	while (1)
	{
		input = msh_get_input(env_list);
		msh_process_input(input, &env_list);
		free(input);
		break ;
	}
	msh_clean(&env_list);
	//system("leaks msh -q");
	return (0);
}
