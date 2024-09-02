/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:53:32 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 22:41:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	check_identifier(char *identifier)
{
	if (!ft_isalpha(identifier[0]) && identifier[0] != '_')
		return (0);
	while (*++identifier)
		if (!ft_isalnum(*identifier) && *identifier != '_')
			return (0);
	return (1);
}

static int	print_invalid_argument(char *arg_str)
{
	ft_putstr_fd("msh: export: -", 2);
	ft_putchar_fd(arg_str[1], 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("export: usage: export [name[=value] ...]", 2);
	return (2);
}

static char	*get_key(char *arg_str, char **value, int *exit_status)
{
	char	*key;

	*value = 0;
	*value = ft_strchr(arg_str, '=');
	if (*value)
		**value = 0;
	key = ft_strdup(arg_str);
	if (!key)
	{
		msh_perror_exit("Export key no mem", EXIT_FAILURE);
		return (0);
	}
	if (!check_identifier(key))
	{
		ft_putstr_fd("msh: export: `", 2);
		if (*value)
			**value = '=';
		ft_putstr_fd(arg_str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*exit_status = 1;
		ft_memdel((void **)&key);
		return (0);
	}
	return (key);
}

int	msh_builtins_func_export(
		int argc __attribute((unused)),
		char **argv,
		t_list **env_list,
		int subshell_flag __attribute((unused))
)
{
	int		exit_status;
	int		i;
	char	*key;
	char	*value;

	if (argv[1] && argv[1][0] == '-')
		return (print_invalid_argument(argv[1]));
	exit_status = 0;
	i = 0;
	while (argv[++i])
	{
		key = 0;
		key = get_key(argv[i], &value, &exit_status);
		if (!key || !value)
		{
			ft_memdel((void **)&key);
			continue ;
		}
		value = ft_strdup(++value);
		if (!value)
			msh_perror_exit("Export value no mem", EXIT_FAILURE);
		msh_env_setvar(env_list, key, value);
	}
	return (exit_status);
}
