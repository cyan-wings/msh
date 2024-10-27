/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:37:15 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:11:44 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"
#include "readline.h"

static void	too_many_args_error(int argc)
{
	if (argc > 2)
		ft_putendl_fd("bash: exit: too many arguments", 2);
}

static int	not_numeric(char *str)
{
	if (ft_strlen(str) > 20)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		++str;
	}
	return (0);
}

static int	msh_builtins_exit_helper(char *exit_arg_str,
		unsigned char exit_status)
{
	long	exit_arg_value;
	char	*temp;

	exit_arg_value = ft_atol(exit_arg_str);
	temp = ft_itol(exit_arg_value);
	if (!temp)
		return (msh_perror_exit_int("msh_builtins_exit", "temp",
				"malloc fail.", EXIT_FAILURE));
	if (not_numeric(exit_arg_str) || ft_strcmp(exit_arg_str, temp))
	{
		ft_putstr_fd("msh: exit: ", 2);
		ft_putstr_fd(exit_arg_str, 2);
		ft_putendl_fd("numeric argument required", 2);
		exit_status = 255;
	}
	else
		exit_status = (unsigned char)(exit_arg_value % 256);
	ft_memdel((void **) &temp);
	return (exit_status);
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
int	msh_builtins_exit(int argc, char **argv, int subshell_flag)
{
	unsigned char	exit_status;
	char			*temp;

	if (!subshell_flag && isatty(STDERR_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	exit_status = 0;
	if (argc == 1)
		exit(exit_status);
	if (argc > 2)
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		ft_memdel((void **) &temp);
		return (EXIT_FAILURE);
	}
	else
		exit_status = msh_builtins_exit_helper(argv[1], exit_status);
	rl_clear_history();
	exit(exit_status);
	ft_putendl_fd("exit", 1);
	return (0);
}

int	msh_builtins_func_exit(int argc, char **argv,
		t_list **env_list __attribute((unused)),
		int subshell_flag)
{
	too_many_args_error(argc);
	return (msh_builtins_exit(argc, argv, subshell_flag));
}
