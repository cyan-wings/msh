/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:36:59 by myeow             #+#    #+#             */
/*   Updated: 2024/09/05 14:29:24 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_lst_utils.h"
#include "ft_string_utils.h"
#include <stdio.h>

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

char	*msh_prompt(t_list *env_list);

static char	*msh_get_input(t_list *env_list)
{
	char	*prompt;
	char	*input;

	prompt = msh_prompt(env_list);
	input = readline(prompt);
	if (!input)
		return (0);
	if (*input)
		msh_save_history(input, HISTORY_FILE);
	printf("The input was: %s\n", input);
	ft_memdel((void **) &prompt);
	return (input);
}

static void	print_error_and_clean(char *err_str, t_list **token_list,
		t_ast **root)
{
	if (*root)
		msh_parse_astfree(root);
	if (*token_list)
		msh_tokenise_free(token_list);
	if (err_str)
		msh_perror(err_str);
	return ;
}

static void	msh_process_input(char *input, t_list **env_list,
		t_global *global)
{
	t_list	*token_list;
	t_ast	*root;
	int		flag;

	token_list = NULL;
	root = 0;
	flag = 0;
	flag = msh_tokenise(input, &token_list);
	if (!flag)
		return (print_error_and_clean("Tokenise error.", &token_list, &root));
	msh_tokenise_print_token_list(token_list);
	flag = msh_parse(token_list, &root);
	if (!flag)
		return (print_error_and_clean("Parsing error.", &token_list, &root));
	msh_parse_astprint(root, 0);
	puts("Parse success.");
	msh_expansion(root, *env_list);
	msh_parse_astprint(root, 0);
	puts("Expansion success.");
	msh_execute(root, env_list, global);
	print_error_and_clean(NULL, &token_list, &root);
}

static void	msh_clean(t_list **env_list)
{
	msh_env_free(env_list);
}

void	msh_init_signal(void);

//system("leaks msh -q");
int	main(void)
{
	t_global	global;
	t_list		*env_list;
	char		*input;

	global = (t_global){0};
	env_list = NULL;
	msh_init(&env_list);
	input = NULL;
	while (1)
	{
		msh_init_signal();
		input = msh_get_input(env_list);
		if (!input)
			exit(0);
		msh_process_input(input, &env_list, &global);
		free(input);
	}
	msh_clean(&env_list);
	return (0);
}
