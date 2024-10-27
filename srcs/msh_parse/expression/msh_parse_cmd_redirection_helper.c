/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_redirection_helper.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:44 by myeow             #+#    #+#             */
/*   Updated: 2024/10/26 21:06:28 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh_signal.h"
#include "msh_expansion.h"

int		msh_parse_cmd_redirection_helper_heredoc(char *delim,
			char **heredoc_contents);

static int	expand_lim(char *lim, char **expanded_lim)
{
	char	*lim_cpy;
	int		flag_dollar_expand;
	int		i;

	lim_cpy = NULL;
	lim_cpy = msh_utils_strdup(lim, "msh_parse_redirection_helper",
			"expand_lim");
	flag_dollar_expand = 1;
	i = -1;
	while (lim_cpy[++i])
		if (lim_cpy[i] == '\'' || lim[i] == '\"')
			flag_dollar_expand = 0;
	if (!flag_dollar_expand)
		msh_expansion_quotes(&lim_cpy);
	if (!lim_cpy)
		lim_cpy = msh_utils_memalloc(1, "msh_parse_redirection_helper",
				"parse_redirection_heredoc: memalloc");
	*expanded_lim = lim_cpy;
	return (flag_dollar_expand);
}

static int	redirection_heredoc(char *lim, t_ast **redir_file)
{
	int		status;
	char	*expanded_lim;
	char	*redir_node_type;
	char	*heredoc_contents;

	status = 0;
	expanded_lim = NULL;
	redir_node_type = NULL;
	if (expand_lim(lim, &expanded_lim))
		redir_node_type = "heredoc";
	else
		redir_node_type = "heredoc_quoted";
	heredoc_contents = NULL;
	status = msh_parse_cmd_redirection_helper_heredoc(expanded_lim,
			&heredoc_contents);
	*redir_file = msh_parse_astnew(redir_node_type, heredoc_contents);
	ft_memdel((void **)&heredoc_contents);
	return (status);
}

int	msh_parse_redirection_helper(t_token *curr, t_token *next,
					t_ast **redir_child_node)
{
	char	*redir_op;
	t_ast	*redir_file;
	int		status;

	redir_op = curr->value;
	redir_file = NULL;
	status = 0;
	if (!ft_strcmp(redir_op, "<<"))
	{
		status = redirection_heredoc(next->value, &redir_file);
		signal(SIGINT, msh_signal_ctrl_c);
	}
	else
		redir_file = msh_parse_astnew("file", next->value);
	*redir_child_node = msh_parse_astnew("redirection", redir_op);
	msh_parse_astadd_child(*redir_child_node, redir_file);
	return (status);
}
