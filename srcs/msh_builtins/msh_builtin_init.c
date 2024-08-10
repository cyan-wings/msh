/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:39:19 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:39:33 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_builtin_init(t_bif **builtin_list)
{
	builtin_list[0] = echo;
	builtin_list[1] = cd;
	builtin_list[2] = pwd;
	builtin_list[3] = export;
	builtin_list[4] = unset;
	builtin_list[5] = env;
	builtin_list[6] = exit;
}
