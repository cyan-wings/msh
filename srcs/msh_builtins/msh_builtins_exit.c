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

static void	too_many_args_error(int argc)
{
	if (argc > 2)
		ft_putendl_fd("bash: exit: too many arguments");
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

static void	msh_builtins_exit_helper(char *exit_arg_str)
{
	long	exit_arg_value;
	char	*temp;

	exit_arg_value = ft_atol(exit_arg_str);
	temp = ft_itol(exit_arg_value);
	if (not_numeric(exit_arg_str) || ft_strcmp(exit_arg_str, temp))
	{
		ft_putstr_fd("msh: exit: ", 2);
		ft_putstr_fd(argv[1]);
		ft_putendl_fd("numeric argument required", 2);
		exit_status = 255;
	}
	else
		exit_status = exit_arg_value % 256;
	ft_memdel((void **) &temp);
}

/*
 * Input type may change to ast node.
 */
int	msh_builtins_exit(int argc, char **argv, int subshell_flag)
{
	unsigned char	exit_status;
	long			exit_arg_value;
	char			*temp;

	if (!subshell_flag && isatty(STDERR_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	exit_status = 0;
	if (argc == 1)
		exit(exit_status);
	if (argc > 2)
	{
		ft_putendl_fd("bash: exit: too many arguments");
		ft_memdel((void **) &temp);
		return (EXIT_FAILURE);
	}
	else
		msh_builtins_exit_helper(argv[1]);
	exit(exit_status);
}
