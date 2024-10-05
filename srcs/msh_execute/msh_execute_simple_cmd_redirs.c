/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_redirs.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:42:13 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 21:43:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "msh_execute.h"

static void	check_params(t_ast *redirs_node, t_redir_st ***redir_st_arr)
{
	if (!redirs_node)
		return (msh_perror_exit("debug", "msh_execute_simple_cmd_redirs",
				"redirs_node is NULL.", EXIT_FAILURE));
	if (!redir_st_arr)
		return (msh_perror_exit("debug", "msh_execute_simple_cmd_redirs",
				"redir_st_arr is NULL.", EXIT_FAILURE));
	if (ft_strcmp(redirs_node->type, "redirections"))
		return (msh_perror_exit("debug", "msh_execute_simple_cmd_redirs",
				"redirs_node is incorrect", EXIT_FAILURE));
}

int	msh_execute_simple_cmd_redirs_process(char *op, char *file,
		t_redir_st ***redir_st_arr);

int	msh_execute_simple_cmd_redirs(t_ast *redirs_node,
	t_redir_st ***redir_st_arr)
{
	int		i;

	check_params(redirs_node, redir_st_arr);
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
	i = -1;
	while (++i < redirs_node->child_count)
	{
		if (msh_execute_simple_cmd_redirs_process(
			redirs_node->children[i]->value,
			redirs_node->children[i]->children[0]->value, redir_st_arr)
			== ERROR)
			return (ERROR);
	}
	return (0);
}
