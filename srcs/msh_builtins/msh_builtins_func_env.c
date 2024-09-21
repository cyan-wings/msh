/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:53:04 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 19:03:41 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_builtins.h"

static int	print_invalid_argument(char *arg_str)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(arg_str[1], 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: env", 2);
	return (1);
}

static int	print_invalid_file_dir(char *arg_str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(arg_str, 2);
	ft_putendl_fd(": Does not support file or directory arguments yet", 2);
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
	if (argv[1] && argv[1][0] == '-')
		return (print_invalid_argument(argv[1]));
	if (argv[1])
		return (print_invalid_file_dir(argv[1]));
	msh_env_print(*env_list);
	return (0);
}
