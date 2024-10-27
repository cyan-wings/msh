/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:53:32 by myeow             #+#    #+#             */
/*   Updated: 2024/10/26 20:06:23 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_builtins.h"

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
	char	*tmp;

	tmp = NULL;
	ft_strvappend(&tmp, "export: -", arg_str[1], NULL);
	if (!tmp)
		return (msh_perror_exit_int("msh_builtins_func_export",
				"print_invalid_argument", "malloc fail.", EXIT_FAILURE));
	msh_perror(tmp, "invalid option\nexport",
		"usage: export [name[=value] ...]");
	ft_memdel((void **)&tmp);
	return (2);
}

//'=' is changed to a '\0' to separate the key and value to 2 strings.
//This is to avoid malloc.
static char	*get_key(char *arg_str, char **value, int *exit_status)
{
	char	*key;

	*value = ft_strchr(arg_str, '=');
	if (*value)
		**value = 0;
	key = msh_utils_strdup(arg_str, "msh_builtins_func_export", "get_key: key");
	if (!check_identifier(key))
	{
		if (*value)
			**value = '=';
		msh_perror("export: `", arg_str, "': not a valid identifier");
		*exit_status = 1;
		ft_memdel((void **)&key);
		return (NULL);
	}
	return (key);
}

static void	msh_builtins_func_export_helper(
		char **argv,
		t_list **env_list,
		int *exit_status
)
{
	int		i;
	char	*key;
	char	*value;
	int		flag;

	i = 0;
	while (argv[++i])
	{
		key = NULL;
		value = NULL;
		key = get_key(argv[i], &value, exit_status);
		if (!key || !value)
		{
			ft_memdel((void **)&key);
			continue ;
		}
		value = msh_utils_strdup(++value, "msh_builtins_func_export", "value");
		flag = 0;
		if (msh_env_getvar(*env_list, key))
			flag = 1;
		msh_env_setvar(env_list, key, value);
		if (flag)
			ft_memdel((void **)&key);
	}
}

int	msh_builtins_func_export(
		int argc __attribute((unused)),
		char **argv,
		t_list **env_list,
		int subshell_flag __attribute((unused))
)
{
	int	exit_status;

	if (!argv[1])
	{
		msh_env_print(*env_list, 1);
		return (0);
	}
	if (argv[1] && argv[1][0] == '-')
		return (print_invalid_argument(argv[1]));
	exit_status = 0;
	msh_builtins_func_export_helper(argv, env_list, &exit_status);
	return (exit_status);
}
