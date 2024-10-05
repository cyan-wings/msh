/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:55:56 by myeow             #+#    #+#             */
/*   Updated: 2024/09/07 00:38:09 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_tokenise.h"
#include "msh_parse.h"
#include "msh_expansion.h"
#include "msh_execute.h"

static int	check_null_param(char *input, t_list **env_list)
{
	int	flag;

	flag = 1;
	if (!input)
	{
		msh_perror("debug", "msh_input_process", "input is NULL.");
		flag = 0;
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_input_process", "env_list is NULL.");
		flag = 0;
	}
	return (flag);
}

static void	print_error_and_clean(char *err_str, t_list **token_list,
		t_ast **root)
{
	if (*root)
		msh_parse_astfree(root);
	if (*token_list)
		msh_tokenise_free(token_list);
	if (err_str)
		msh_perror(NULL, NULL, err_str);
	return ;
}

//Must free input and env_list when failure and exit.
void	msh_input_process(char *input, t_list **env_list)
{
	t_list	*token_list;
	t_ast	*root;
	int		flag;

	if (!check_null_param(input, env_list))
		return ;
	token_list = NULL;
	root = NULL;
	flag = 0;
	flag = msh_tokenise(input, &token_list);
	if (!flag)
		return (print_error_and_clean("Tokenise error.", &token_list, &root));
	msh_tokenise_print_token_list(token_list);
	flag = msh_parse(token_list, &root);
	if (!flag)
		return (print_error_and_clean("Parsing error.", &token_list, &root));
	msh_parse_astprint(root, 0);
	ft_putendl_fd("Parse success.", 1);
	msh_expansion(root, *env_list);
	msh_parse_astprint(root, 0);
	ft_putendl_fd("Expansion success.", 1);
	msh_execute(root->children[0], env_list, 0);
	print_error_and_clean(NULL, &token_list, &root);
}
