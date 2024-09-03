/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:48:25 by myeow             #+#    #+#             */
/*   Updated: 2024/09/03 16:38:45 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "msh.h"

static int	print_invalid_argument(char *arg_str)
{
	ft_putstr_fd("msh: cd: ", 2);
	ft_putchar_fd(arg_str[0], 2);
	ft_putchar_fd(arg_str[1], 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("cd: usage: cd [dir, -]", 2);
	return (1);
}

/*
 * First if condition is checking if cd has no arguments.
 * Not passing argc as parameter to adhere norme.
 */
static void	get_dir(char **argv, t_list **env_list, char **dir, int *is_home)
{
	*dir = 0;
	*is_home = 0;
	if (!argv[1])
	{
		*dir = msh_env_getvar(*env_list, "HOME");
		if (!*dir)
			ft_putendl_fd("msh: cd: HOME not set", 2);
	}
	else if (argv[1] && !ft_strcmp(argv[1], "-"))
	{
		*dir = msh_env_getvar(*env_list, "OLDPWD");
		if (!*dir)
			ft_putendl_fd("msh: cd: OLDPWD not set", 2);
		*is_home = 1;
	}
	else
		*dir = argv[1];
}

static int	get_change_dir_exit_status(char *dir, struct stat *statbuf)
{
	if (stat(dir, statbuf) == -1)
	{
		ft_putendl_fd("stat error.", 1);
		return (1);
	}
	if (!S_ISDIR((*statbuf).st_mode))
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	if ((*statbuf).st_mode & S_IXUSR)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	if (chdir(dir) == -1)
	{
		ft_putendl_fd("chdir error.", 1);
		return (1);
	}
	return (0);
}

/*
 * This differs from bash.
 * OLDPWD and PWD is set regardless whether env var is present or not.
 * Bash only updates if either of these are available as env_vars.
 */
static void	update_pwd_env_var(t_list **env_list,
		char *prev_dir, char *changed_dir)
{
	msh_env_setvar(env_list, "OLDPWD", prev_dir);
	msh_env_setvar(env_list, "PWD", changed_dir);
}

int	msh_builtins_func_cd(
		int argc __attribute((unused)),
		char **argv, t_list **env_list,
		int subshell_flag __attribute((unused))
)
{
	char		*dir;
	int			is_home;
	char		curr_dir[PATH_MAX];
	struct stat	statbuf;

	if (argv[1] && argv[1][0] == '-' && argv[1][1])
		return (print_invalid_argument(argv[1]));
	get_dir(argv, env_list, &dir, &is_home);
	if (!dir)
		return (1);
	if (!getcwd(curr_dir, sizeof(curr_dir)))
	{
		ft_putendl_fd("getcwd error.", 1);
		return (1);
	}
	if (get_change_dir_exit_status(dir, &statbuf))
		return (1);
	if (is_home)
		ft_putendl_fd(dir, 2);
	update_pwd_env_var(env_list, curr_dir, dir);
	return (0);
}
