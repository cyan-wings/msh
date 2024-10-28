/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_get_builtin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:11:56 by myeow             #+#    #+#             */
/*   Updated: 2024/10/28 18:49:57 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_builtins.h"

int	msh_builtins_func_cd(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_echo(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_env(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_export(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_pwd(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_unset(int argc, char **argv, t_list **env_list,
		int subshell_flag);

static t_bif	*get_builtin_func(int i, int len)
{
	static t_bif	builtin_func[] = {
		msh_builtins_func_cd,
		msh_builtins_func_echo,
		msh_builtins_func_env,
		msh_builtins_func_export,
		msh_builtins_func_pwd,
		msh_builtins_func_unset,
		NULL
	};

	if (i < 0 || i >= len)
		return (NULL);
	return (&builtin_func[i]);
}

t_bif	*msh_builtins_get_builtin(char *executable)
{
	const char	*builtin_list[] = {
		"cd",
		"echo",
		"env",
		"export",
		"pwd",
		"unset",
		NULL
	};
	int			len;
	int			i;

	len = msh_utils_arraylen((char **)builtin_list);
	i = -1;
	while (++i < len)
		if (!ft_strcmp(executable, builtin_list[i]))
			return (get_builtin_func(i, len));
	return (NULL);
}
