/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:53:04 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 01:02:27 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_builtins.h"

static int	print_env_ret(t_list **env_list)
{
	msh_env_print(*env_list, 0);
	return (0);
}

static int	unsupported_args(char **argv)
{
	msh_perror("env", argv[1],
		"Does not support file or directory arguments yet.");
	return (127);
}

/* 
 * This env builtin does not handle any options/flags.
 * argv[0] is executable.
 * argv[1] is the first argument.
 *
 * @return:
 * 		0 - if all identifiers are valid and no errors.
 * 		1 - when the first argument starts with character '-'.
 * 		127 - when there is one or more arguments since this has 
 * 				yet to support files or directories.
 */
int	msh_builtins_func_env(
		int argc __attribute((unused)),
		char **argv __attribute((unused)),
		t_list **env_list,
		int subshell_flag __attribute((unused))
)
{
	if (argv[1])
	{
		if (!ft_strcmp(argv[1], "--"))
			return (print_env_ret(env_list));
		else if (argv[1][0] == '-' && argv[1][1])
		{
			ft_putstr_fd("msh: env: illegal option --", STDERR_FILENO);
			ft_putchar_fd(argv[1][1], STDERR_FILENO);
			ft_putendl_fd("\nusage: env", STDERR_FILENO);
			return (1);
		}
		else if (argv[1][0] == '-')
			return (0);
		else
			return (unsupported_args(argv));
	}
	return (print_env_ret(env_list));
}
