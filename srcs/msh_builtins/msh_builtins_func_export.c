/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:53:32 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 20:47:35 by myeow            ###   ########.fr       */
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

static void	export_var_to_env_list(t_list **env_list, char *key, char *value)
{
	char	*k;
	char	*v;

	k = ft_strdup(key);
	v = ft_strdup(value);
	if (!k || !v)
		return (msh_perror_exit("Export key val no mem", EXIT_FAILURE));
	msh_env_setvar(env_list, k, v);
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
	char	*equals;
	char	*key;
	char	*value;

	if (argv[1] && argv[1][0] == '-')
		return (print_invalid_argument(argv[1]));
	msh_env_print(*env_list);
	exit_status = 0;
	i = 0;
	while (argv[++i])
	{
		equals = 0;
		equals = ft_strchr(argv[i], '=');
		if (!equals)
			continue;
		*equals = 0;
		key = argv[i];
		if (!check_identifier(key))
		{
			ft_putstr_fd("msh: export: `", 2);
			*equals = '=';
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exit_status = 1;
			continue;
		}
		value = equals + 1;
		export_var_to_env_list(env_list, key, value);
	}
	msh_env_print(*env_list);
	return (exit_status);
}
