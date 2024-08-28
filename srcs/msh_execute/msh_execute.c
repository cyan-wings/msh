/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:29:42 by myeow             #+#    #+#             */
/*   Updated: 2024/08/28 18:35:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_execute_traverse_nodes(t_ast *node, t_list **env_list,
		t_bif *builtin_list, t_global *global);

int	msh_execute(t_ast *node, t_list **env_list,
		t_bif *builtin_list, t_global *global)
{
	return (msh_execute_traverse_nodes(node, env_list, builtin_list, global));
}
