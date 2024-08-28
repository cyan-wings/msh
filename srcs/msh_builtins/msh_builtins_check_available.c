/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_check_available.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:18:28 by myeow             #+#    #+#             */
/*   Updated: 2024/08/28 20:20:26 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"

int	msh_builtins_check_available(char *executable)
{
	const char	*builtin_list[] = {
		"cd",
		"export",
		"exit",
		"unset",
		"echo",
		"pwd",
		"env"
	};
	int			i;

	i = -1;
	while (++i < 7)
		if (!ft_strcmp(executable, builtin_list[i]))
			return (1);
	return (0);
}
