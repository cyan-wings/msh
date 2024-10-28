/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:37:15 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:11:44 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"
#include "readline.h"

static int	not_valid_number(char *str)
{
	if (ft_strlen(str) > 20)
		return (1);
	if (*str == '+' || *str == '-')
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		++str;
	}
	return (0);
}

static int	process_arg(char *exit_arg_str)
{
	long	exit_arg_value;
	char	*temp;
	int		status;

	if (not_valid_number(exit_arg_str))
	{
		msh_perror("exit", exit_arg_str, "numeric argument required");
		return (255);
	}
	exit_arg_value = ft_atol(exit_arg_str);
	temp = ft_itol(exit_arg_value);
	if (!temp)
		return (msh_perror_exit_int("msh_builtins_exit", "temp",
				"malloc fail.", EXIT_FAILURE));
	if (exit_arg_str[0] == '+')
		++exit_arg_str;
	if (ft_strcmp(exit_arg_str, temp))
	{
		msh_perror("exit", exit_arg_str, "numeric argument required");
		status = 255;
	}
	else
		status = (unsigned char)(exit_arg_value % 256);
	ft_memdel((void **) &temp);
	return (status);
}

/*
 * Input type may change to ast node.
 *
 * TODO: The current code doesn't exit when invalid arguments.
 * But BASH exits even though the exit arguments are invalid.
 * THe exit status must be passed on when there are subshells.
 *
 * The final "exit" output is mandatory.
 */
int	msh_builtins_exit_helper(int argc, char **argv, int subshell_flag)
{
	unsigned char	status;

	status = 0;
	if (!subshell_flag && isatty(STDERR_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (argc > 2)
	{
		msh_perror("exit", NULL, "too many arguments");
		status = EXIT_FAILURE;
	}
	else if (argc == 2)
		status = process_arg(argv[1]);
	ft_free_ft_split(argv);
	rl_clear_history();
	exit(status);
	return (status);
}

int	msh_builtins_exit(char **argv, int subshell_flag)
{
	int	len;

	len = msh_utils_arraylen(argv);
	return (msh_builtins_exit_helper(len, argv, subshell_flag));
}
