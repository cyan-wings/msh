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
#include "ft_print_utils.h"

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

void	msh_input_process(char *input, t_list **env_list,
		t_global *global)
{
	t_list	*token_list;
	t_ast	*root;
	int		flag;

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
	(void) global;
	msh_execute(root->children[0], env_list);
	print_error_and_clean(NULL, &token_list, &root);
}
