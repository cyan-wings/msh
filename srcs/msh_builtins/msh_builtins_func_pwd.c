/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_pwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:55:44 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 16:16:54 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"
#include "msh.h"

/*
 * Actual pwd runs without any arguments.
 * But when given arguments with a "-", it will flag error without 
 * running pwd.
 * But when the 1st argument is given without a "-", it runs as usual
 * without flagging any errors.
 */
int	msh_builtins_func_pwd(int argc __attribute((unused)), char **argv,
		t_list **env_list, int subshell_flag __attribute((unused)))
{
	if (argv[1] && argv[1][0] == '-')
	{
		ft_putstr_fd("msh: pwd: ", 2);
		ft_putchar_fd(argv[1][0], 2);
		ft_putchar_fd(argv[1][1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd("pwd: usage: pwd", 2);
		return (1);
	}
	ft_putendl_fd(msh_env_getvar(*env_list, "PWD"), 1);
	return (0);
}
