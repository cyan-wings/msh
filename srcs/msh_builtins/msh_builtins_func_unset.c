/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:56:11 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 20:00:58 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char_utils.h"
#include "msh.h"

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

static int	print_invalid_argument(int argc, char *arg_str)
{
	ft_putstr_fd("msh: unset: ", 2);
	ft_putchar_fd(arg_str[0], 2);
	ft_putchar_fd(arg_str[1], 2);
	ft_putendl_fd(":invalid option", 2);
	ft_putendl_fd("unset: usage: unset [name ...]", 2);
	if (argc == 2)
		return (127);
	return (2);
}

/* 
 * This unset builtin does not handle any options/flags.
 * argv[0] is executable.
 * argv[1] is the first argument.
 *
 * @return:
 * 		0 - if all identifiers are valid and no errors.
 * 		1 - when one or more identifiers are invalid.
 * 		2 - when the first argument has a '-' and there is more
 * 				than 1 argument.
 * 		127 - when the first argument has a '-' and there is
 * 				only 1 argument.
 */
int	msh_builtins_func_unset(
		int argc,
		char **argv,
		t_list **env_list __attribute((unused)),
		int subshell_flag __attribute((unused))
)
{
	int	exit_status;
	int	i;

	if (argv[1] && argv[1][0] == '-')
		return (print_invalid_argument(argc, argv[1]));
	exit_status = 0;
	i = 0;
	while (argv[++i])
	{
		if (!check_identifier(argv[i]))
		{
			ft_putstr_fd("msh: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exit_status = 1;
			continue;
		}
		msh_env_delvar(env_list, argv[i]);
	}
	return (exit_status);
}
