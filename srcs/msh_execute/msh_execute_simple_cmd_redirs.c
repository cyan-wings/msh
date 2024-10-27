/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_redirs.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:42:13 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 07:21:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "msh_execute.h"
#include "msh_expansion.h"

static int	check_params(t_ast *redirs_node)

{
	if (!redirs_node)
	{
		msh_perror("debug", "msh_execute_simple_cmd_redirs",
			"redirs_node is NULL.");
		return (0);
	}
	if (ft_strcmp(redirs_node->type, "redirections"))
	{
		msh_perror("debug", "msh_execute_simple_cmd_redirs",
			"node type is incorrect.");
		return (0);
	}
	return (1);
}

static int	expand_file_str_helper(char **file_str_expanded)
{
	char	**array;
	int		i;

	array = NULL;
	array = msh_utils_split(*file_str_expanded, ' ',
			"msh_execute_simple_cmd_redirs", "expand_file_str_helper");
	ft_memdel((void **)file_str_expanded);
	if (msh_utils_arraylen(array) != 1)
	{
		ft_free_ft_split(array);
		return (AMBIGUOUS_REDIR_ERROR);
	}
	*file_str_expanded = msh_utils_strdup(array[0],
			"msh_execute_simple_cmd_redirs", "expand_file_str_helper");
	ft_free_ft_split(array);
	i = -1;
	while ((*file_str_expanded)[++i])
		if ((*file_str_expanded)[i] == SPACE_R)
			(*file_str_expanded)[i] = ' ';
	if (ft_strchr(*file_str_expanded, PAD_R))
		msh_utils_strrpad(file_str_expanded, PAD_R);
	return (0);
}

static int	expand_file_str(char *file_type, char *file_str,
		char **file_str_expanded, t_list **env_list)
{
	if (!file_str)
		return (msh_perror_exit_int("debug", "msh_execute_simple_cmd_redirs",
				"file_str is NULL", EXIT_FAILURE));
	if (ft_strcmp(file_type, "file"))
	{
		*file_str_expanded = msh_utils_strdup(file_str,
				"msh_execute_simple_cmd_redirs", "expand_file_str");
		if (!ft_strcmp(file_type, "heredoc"))
			msh_expansion_dollar(file_str_expanded, *env_list, 0);
		return (0);
	}
	*file_str_expanded = msh_expansion_word(file_str, *env_list);
	if (!*file_str_expanded || !ft_strlen(*file_str_expanded))
	{
		ft_memdel((void **)file_str_expanded);
		return (AMBIGUOUS_REDIR_ERROR);
	}
	if (ft_strchr(*file_str_expanded, DELIM_R))
	{
		ft_memdel((void **)file_str_expanded);
		return (AMBIGUOUS_REDIR_ERROR);
	}
	return (expand_file_str_helper(file_str_expanded));
}

int		msh_execute_simple_cmd_redirs_process(char *op, char *file,
				t_redir_st ***redir_st_arr);

static int	msh_execute_simple_cmd_redirs_helper(t_ast *redirs_node,
	t_redir_st ***redir_st_arr, t_list **env_list)
{
	int		i;
	char	*op;
	char	*file_type;
	char	*file_str;
	char	*file_str_expanded;

	i = -1;
	while (++i < redirs_node->child_count)
	{
		op = NULL;
		file_type = NULL;
		file_str = NULL;
		op = redirs_node->children[i]->value;
		file_type = redirs_node->children[i]->children[0]->type;
		file_str = redirs_node->children[i]->children[0]->value;
		file_str_expanded = NULL;
		if (expand_file_str(file_type, file_str, &file_str_expanded,
				env_list) == AMBIGUOUS_REDIR_ERROR)
			return (msh_perror_int(file_str, NULL, "ambiguous redirect"));
		if (msh_execute_simple_cmd_redirs_process(op, file_str_expanded,
				redir_st_arr) == ERROR)
			return (ERROR);
	}
	return (0);
}

//redir_st_arr can be NULL if no fd restoration is needed.
int	msh_execute_simple_cmd_redirs(t_ast *redirs_node,
	t_redir_st ***redir_st_arr, t_list **env_list)
{
	if (!check_params(redirs_node))
		return (ERROR);
	if (!redirs_node->child_count)
		return (0);
	if (redir_st_arr)
	{
		*redir_st_arr = (t_redir_st **)ft_calloc(redirs_node->child_count + 1,
				sizeof(t_redir_st *));
		if (!*redir_st_arr)
			return (msh_perror_exit_int("msh_execute_simple_cmd_redirs",
					"redir_st_arr", "malloc fail.", EXIT_FAILURE));
	}
	return (msh_execute_simple_cmd_redirs_helper(redirs_node, redir_st_arr,
			env_list));
}
