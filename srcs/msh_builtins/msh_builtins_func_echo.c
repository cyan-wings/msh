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

#include "msh.h"

int	msh_builtins_func_echo(
		int argc __attribute((unused)),
		char **argv,
		t_list **env_list __attribute((unused)),
		int subshell_flag __attribute((unused)))
{
	int	no_newline;
	int	i;

	no_newline = 0;
	if (argv[1] && !ft_strcmp(argv[1], "-n"))
		no_newline = 1;
	i = no_newline;
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
