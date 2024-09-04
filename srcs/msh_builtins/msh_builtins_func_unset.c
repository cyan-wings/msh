/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:56:11 by myeow             #+#    #+#             */
/*   Updated: 2024/09/04 19:16:04 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char_utils.h"
#include "msh.h"

#define RESTRICTED_ENV_VARS 3

static int	print_invalid_argument(char *arg_str)
{
	if (!ft_strcmp(arg_str, "-"))
	{
		ft_putendl_fd("msh: unset: `-': not a valid identifier", 2);
		return (1);
	}
	ft_putstr_fd("msh: unset: ", 2);
	ft_putchar_fd(arg_str[0], 2);
	ft_putchar_fd(arg_str[1], 2);
	ft_putendl_fd(":invalid option", 2);
	ft_putendl_fd("unset: usage: unset [name ...]", 2);
	return (2);
}

static int	check_restricted(char *identifier)
{
	const char	*lst[] = {"HOME", "PWD", "OLDPWD"};
	int			i;

	i = -1;
	while (++i < RESTRICTED_ENV_VARS)
	{
		if (!ft_strcmp(lst[i], identifier))
		{
			ft_putendl_fd("Restrictied env_vars cannot be unset.", 2);
			return (1);
		}
	}
	return (0);
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
		if (check_restricted(argv[i]))
			continue ;
		if (!check_identifier(argv[i]))
		{
			ft_putstr_fd("msh: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exit_status = 1;
			continue ;
		}
		msh_env_delvar(env_list, argv[i]);
	}
	msh_env_print(*env_list);
	return (exit_status);
}
