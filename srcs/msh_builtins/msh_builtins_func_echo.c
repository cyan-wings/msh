/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_echo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:52:38 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 23:04:39 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

static void	process_n_helper(char **argv, int i, int *flag)
{
	int	j;

	j = 1;
	while (argv[i][++j])
	{
		if (argv[i][j] != 'n')
		{
			*flag = 0;
			break ;
		}
	}
}

static int	process_n(int argc, char **argv, int *no_newline)
{
	int	flag;
	int	i;

	flag = 1;
	i = 0;
	while (flag && ++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'n')
			process_n_helper(argv, i, &flag);
		else
			break ;
	}
	if (i > 1)
		*no_newline = 1;
	return (i);
}

int	msh_builtins_func_echo(
		int argc,
		char **argv,
		t_list **env_list __attribute((unused)),
		int subshell_flag __attribute((unused)))
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
		i = process_n(argc, argv, &no_newline);
	--i;
	while (argv[++i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (!no_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
