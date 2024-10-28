/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:56:11 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 17:07:38 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_builtins.h"

static int	print_invalid_argument(char *arg_str)
{
	if (!ft_strcmp(arg_str, "-"))
	{
		msh_perror("unset", "`-'", "not a valid identifier");
		return (1);
	}
	ft_putstr_fd("msh: unset: ", STDERR_FILENO);
	ft_putchar_fd(arg_str[0], STDERR_FILENO);
	ft_putchar_fd(arg_str[1], STDERR_FILENO);
	ft_putendl_fd(": invalid option\nunset: usage: unset [name ...]",
		STDERR_FILENO);
	return (2);
}

/*
 * Identifier syntax is similar to code variables where no special symbols
 * are allowed except _ and 1st character must always be alphabet only.
 */
static int	check_identifier(char *identifier)
{
	if (!ft_isalpha(identifier[0]) && identifier[0] != '_')
		return (0);
	while (*++identifier)
		if (!ft_isalnum(*identifier) && *identifier != '_')
			return (0);
	return (1);
}

/* 
 * This unset builtin does not handle any options/flags.
 * argv[0] is executable.
 * argv[1] is the first argument.
 * This differs from bash where some env_vars are restricted.
 *
 * @return:
 * 		0 - if all identifiers are valid and no errors.
 * 		1 - when one or more identifiers are invalid.
 * 		2 - when the first argument start with '-' with other characters
 */
int	msh_builtins_func_unset(
		int argc __attribute((unused)),
		char **argv,
		t_list **env_list __attribute((unused)),
		int subshell_flag __attribute((unused))
)
{
	int	exit_status;
	int	i;

	if (argv[1] && argv[1][0] == '-')
		return (print_invalid_argument(argv[1]));
	exit_status = 0;
	i = 0;
	while (argv[++i])
	{
		if (msh_env_check_restricted(argv[i], "unset"))
			continue ;
		if (!check_identifier(argv[i]))
		{
			msh_perror("unset", argv[i], "not a valid identifier");
			exit_status = 1;
			continue ;
		}
		msh_env_delvar(env_list, argv[i]);
	}
	return (exit_status);
}
