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

char	*msh_expansion_word(char *word, t_list *env_list);

static int	redirection_expand_helper(char **array, t_ast **redir_file_node)
{
	char	*file_str;
	int		i;

	file_str = NULL;
	file_str = msh_utils_strdup(array[0], "msh_parse_cmd_redirection",
			"redirection_expand_helper");
	ft_free_ft_split(array);
	i = -1;
	while (file_str[++i])
		if (file_str[i] == SPACE_R)
			file_str[i] = ' ';
	msh_utils_strrpad(&(file_str), PAD_R);
	*redir_file_node = msh_parse_astnew("file", file_str);
	ft_memdel((void **)&file_str);
	return (0);
}

static int	redirection_expand(char *redir_str, t_ast **redir_file_node,
					t_list *env_list)
{
	char	*out;
	char	**array;

	out = NULL;
	out = msh_expansion_word(redir_str, env_list);
	if (!out || !ft_strlen(out))
		return (AMBIGUOUS_REDIR_ERROR);
	if (ft_strchr(out, DELIM_R))
	{
		ft_memdel((void **)&out);
		return (AMBIGUOUS_REDIR_ERROR);
	}
	array = NULL;
	array = msh_utils_split(out, ' ', "msh_parse_cmd_redirection",
			"redirection_expand");
	ft_memdel((void **)&out);
	if (msh_utils_arraylen(array) != 1)
	{
		ft_free_ft_split(array);
		return (AMBIGUOUS_REDIR_ERROR);
	}
	return (redirection_expand_helper(array, redir_file_node));
}

static int	parse_redirection_heredoc(char *lim, t_list *env_list,
		char **heredoc_contents)
{
	char	*lim_cpy;
	int		flag_dollar_expand;
	int		i;
	int		status;

	lim_cpy = msh_utils_strdup(lim, "msh_parse_redirection_helper",
			"parse_redirection_heredoc");
	flag_dollar_expand = 1;
	i = -1;
	while (lim_cpy[++i])
		if (lim_cpy[i] == '\'' || lim_cpy[i] == '\"')
			flag_dollar_expand = 0;
	if (!flag_dollar_expand)
		msh_expansion_quotes(&lim_cpy);
	if (!lim_cpy)
		lim_cpy = msh_utils_memalloc(1, "msh_parse_redirection_helper",
				"parse_redirection_heredoc: memalloc");
	status = 0;
	status = msh_parse_cmd_redirection_helper_heredoc(lim_cpy,
			heredoc_contents);
	if (flag_dollar_expand && *heredoc_contents)
		msh_expansion_dollar(heredoc_contents, env_list, 0);
	return (status);
}

int	msh_parse_redirection_helper(t_token *curr, t_token *next,
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
		heredoc_contents = NULL;
		status = parse_redirection_heredoc(next->value, env_list,
				&heredoc_contents);
		redir_file = msh_parse_astnew("heredoc", heredoc_contents);
		ft_memdel((void **)&heredoc_contents);
		signal(SIGINT, msh_signal_ctrl_c);
	}
	else
		status = redirection_expand(next->value, &redir_file, env_list);
	*redir_child_node = msh_parse_astnew("redirection", redir_op);
	msh_parse_astadd_child(*redir_child_node, redir_file);
	return (status);
}
