/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:55:56 by myeow             #+#    #+#             */
/*   Updated: 2024/10/18 17:01:24 by myeow            ###   ########.fr       */
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
	{
		msh_perror(NULL, NULL, err_str);
		msh_execute_exit_status_set(EXIT_FAILURE);
	}
	errno = 0;
	return ;
}

static int	process_tokenise(char *input, t_list **env_list,
		t_list	**token_list)
{
	int		status;
	char	*tmp;

	if (!*input)
		return (1);
	status = 0;
	status = msh_tokenise(input, token_list);
	if (status)
		return (status);
	tmp = NULL;
	tmp = msh_env_getvar(*env_list, "MSH_DEBUG_TOKEN");
	if (tmp && !ft_strcmp(tmp, "true"))
		msh_tokenise_print_token_list(*token_list);
	return (status);
}

static void	msh_input_process_helper(t_list **env_list, t_ast *root)
{
	char	*tmp;

	tmp = NULL;
	tmp = msh_env_getvar(*env_list, "MSH_DEBUG_PARSE");
	if (tmp && !ft_strcmp(tmp, "true"))
	{
		msh_parse_astprint(root, 0, 0);
		msh_perror(NULL, NULL, "Parse success.");
	}
	msh_expansion(root, *env_list);
	tmp = msh_env_getvar(*env_list, "MSH_DEBUG_EXPAND");
	if (tmp && !ft_strcmp(tmp, "true"))
	{
		msh_parse_astprint(root, 0, 1);
		msh_perror(NULL, NULL, "Expansion success.");
	}
	msh_execute(root->children[0], env_list, 0);
}

//Must free input and env_list when failure and exit.
void	msh_input_process(char *input, t_list **env_list)
{
	t_list	*token_list;
	t_ast	*root;
	int		status;

	if (!check_null_param(input, env_list))
		return ;
	token_list = NULL;
	root = NULL;
	status = 0;
	status = process_tokenise(input, env_list, &token_list);
	if (status == ERROR)
		return (print_error_and_clean("Tokenise error.", &token_list, &root));
	else if (status == 1)
		return (print_error_and_clean(NULL, &token_list, &root));
	status = msh_parse(token_list, &root);
	if (status == ERROR)
		return (print_error_and_clean("Parsing error.", &token_list, &root));
	else if (status == HEREDOC_SIGINT_ERROR)
		return (print_error_and_clean(NULL, &token_list, &root));
	msh_input_process_helper(env_list, root);
	print_error_and_clean(NULL, &token_list, &root);
}
