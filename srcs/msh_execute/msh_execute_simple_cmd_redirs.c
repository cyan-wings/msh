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

void    msh_execute_simple_cmd_redirs_process(char *op, char *file,
            t_redir_st **redir_st_arr);

void	msh_execute_simple_cmd_redirs_restore(t_redir_st **redir_st_arr);

void	msh_execute_simple_cmd_redirs(t_ast *redirs_node)
{
	t_redir_st	**redir_st_arr;
	int		i;
	t_ast	*redir;

	redir_st_arr = NULL;
	redir_st_arr = (t_redir_st **)ft_calloc(redirs_node->child_count + 1,
						sizeof(t_redir_st *));
	if (!redir_st_arr)
		return (msh_perror_exit("msh_execute_simple_cmd_redirs",
				"redir_st_arr", "malloc fail.", EXIT_FAILURE));
	i = -1;
	redir = NULL;
	while (++i < redirs_node->child_count)
	{
		redir = redirs_node->children[i];
		msh_execute_simple_cmd_redirs_process(redir->value,
			redir->children[0]->value, redir_st_arr);
	}
	msh_execute_simple_cmd_redirs_restore(redir_st_arr);
}
