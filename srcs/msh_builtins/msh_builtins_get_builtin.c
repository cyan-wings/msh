/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_get_builtin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:11:56 by myeow             #+#    #+#             */
/*   Updated: 2024/09/01 17:21:49 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"
#include "msh.h"

#define NO_OF_BUILTINS 7

int	msh_builtins_func_cd(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_echo(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_env(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_exit(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_export(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_pwd(int argc, char **argv, t_list **env_list,
		int subshell_flag);

int	msh_builtins_func_unset(int argc, char **argv, t_list **env_list,
		int subshell_flag);

t_bif	*get_builtin_func(int i)
{
	static t_bif	builtin_func[NO_OF_BUILTINS] = {
		msh_builtins_func_cd,
		msh_builtins_func_echo,
		msh_builtins_func_env,
		msh_builtins_func_exit,
		msh_builtins_func_export,
		msh_builtins_func_pwd,
		msh_builtins_func_unset
	};

	if (i < 0 || i >= NO_OF_BUILTINS)
		return (NULL);
	return (&builtin_func[i]);
}

t_bif	*msh_builtins_get_builtin(char *executable)
{
	const char	*builtin_list[] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset"
	};
	int			i;

	i = -1;
	while (++i < NO_OF_BUILTINS)
		if (!ft_strcmp(executable, builtin_list[i]))
			return (get_builtin_func(i));
	return (NULL);
}
