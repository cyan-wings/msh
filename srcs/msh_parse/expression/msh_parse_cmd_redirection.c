/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:44 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 03:34:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"

static int	check_null_param(t_list **token_ptr,
			t_ast **redirs_root_node, t_list *env_list)
{
	if (!token_ptr)
	{
		msh_perror("debug", "msh_parse_cmd_redirections",
			"token_ptr is NULL.");
		return (0);
	}
	if (!redirs_root_node)
	{
		msh_perror("debug", "msh_parse_cmd_redirections",
			"redirs_root_node is NULL.");
		return (0);
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_parse_cmd_redirections",
			"env_list is NULL.");
		return (0);
	}
	return (1);
}

int		msh_parse_cmd_redirection_heredoc(const char *delim,
				char **heredoc_contents);

int		ft_arraylen(char **array);

void	ft_strrpad(char **strptr, char padding);

static int	redirection_expand_helper(t_token *next, t_ast **redir_file)
{
	char	**array;

	if (ft_strchr(next->value, PAD_R))
	{
		array = NULL;
		array = ft_split(next->value, DELIM_R);
		if (!array)
			return (msh_perror_exit_int("msh_parse_cmd_redirections",
					"redirection_expand", "malloc fail.", EXIT_FAILURE));
		if (ft_arraylen(array) != 1)
		{
			ft_free_ft_split(array);
			return (AMBIGUOUS_REDIR_ERROR);
		}
		ft_strrpad(&(array[0]), PAD_R);
		*redir_file = msh_parse_astnew("file", array[0]);
		ft_free_ft_split(array);
	}
	else
		*redir_file = msh_parse_astnew("file", next->value);
	return (0);
}

static int	redirection_expand(t_token *next, t_ast **redir_file,
					t_list *env_list)
{
	msh_parse_expansion_dollar(&(next->value), env_list, 1);
	msh_parse_expansion_wildcards(&(next->value));
	msh_parse_expansion_quotes(&(next->value));
	if (!(next->value) || !ft_strlen(next->value))
		return (AMBIGUOUS_REDIR_ERROR);
	return (redirection_expand_helper(next, redir_file));
}

static int	parse_redirection(t_token *curr, t_token *next,
					t_ast **redir_child_node, t_list *env_list)
{
	char	*redir_op;
	t_ast	*redir_file;
	int		status;
	char	*heredoc_contents;

	redir_op = curr->value;
	redir_file = NULL;
	status = 0;
	if (!ft_strcmp(redir_op, "<<"))
	{
		msh_parse_expansion_quotes(&next->value);
		heredoc_contents = NULL;
		status = msh_parse_cmd_redirection_heredoc(next->value,
				&heredoc_contents);
		if (heredoc_contents)
			msh_parse_expansion_dollar(&heredoc_contents, env_list, 0);
		redir_file = msh_parse_astnew("heredoc", heredoc_contents);
		ft_memdel((void **)&heredoc_contents);
		signal(SIGINT, msh_signal_ctrl_c);
	}
	else
		status = redirection_expand(next, &redir_file, env_list);
	*redir_child_node = msh_parse_astnew("redirection", redir_op);
	msh_parse_astadd_child(*redir_child_node, redir_file);
	return (status);
}

/*
 * When this function enters current token is assumed to be of REDIR_OP type.
 * Hence, no check is needed.
 * Validation is needed for next token to be a WORD, otherwise parsing fails.
 *
 * Return:	0 if parsing grammar is erronous. 1 if successful.
 *
 * Notes:	Freeing due to error is done outside this function
 * 			on the redirections node.
 */
int	msh_parse_cmd_redirection(t_list **token_ptr,
		t_ast **redirs_root_node, t_list *env_list)
{
	int		status;
	t_ast	*redir_child_node;

	if (!check_null_param(token_ptr, redirs_root_node, env_list))
		return (ERROR);
	status = 0;
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
	{
		if (!((*token_ptr)->next) || \
			((t_token *)(*token_ptr)->next->content)->type != WORD)
			return (ERROR);
		redir_child_node = NULL;
		status = parse_redirection((t_token *)(*token_ptr)->content, \
				(t_token *)(*token_ptr)->next->content, &redir_child_node,
				env_list);
		if (status)
			return (status);
		msh_parse_astadd_child(*redirs_root_node, redir_child_node);
		msh_tokenise_get_next_token(token_ptr);
		msh_tokenise_get_next_token(token_ptr);
	}
	return (status);
}
