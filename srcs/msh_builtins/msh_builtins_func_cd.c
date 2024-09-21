/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:48:25 by myeow             #+#    #+#             */
/*   Updated: 2024/09/03 20:32:37 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "msh_env.h"
#include "msh_builtins.h"

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

static int	print_return_error(char *err_str, char *dir)
{
	ft_putstr_fd("msh: cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putendl_fd(err_str, 2);
	return (1);
}

static int	get_change_dir_exit_status(char *dir)
{
	struct stat	statbuf;

	if (access(dir, F_OK))
		return (print_return_error(": No such file or directory", dir));
	if (stat(dir, &statbuf) == -1)
	{
		ft_putendl_fd("stat error.", 2);
		return (1);
	}
	if (!S_ISDIR(statbuf.st_mode))
		return (print_return_error(": Not a directory", dir));
	if (!(statbuf.st_mode & S_IXUSR))
		return (print_return_error(": Permission denied", dir));
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
 *
 * Special note:
 * 		getcwd can fail when the current directory does not have
 * 		read permissions. This can be tested by creating a 
 * 		test directory with chmod 100.
 */
int	msh_builtins_func_cd(
		int argc __attribute((unused)),
		char **argv, t_list **env_list,
		int subshell_flag __attribute((unused))
)
{
	char		*dir;
	int			is_home;
	char		curr_dir[PATH_MAX];

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
	if (get_change_dir_exit_status(dir))
		return (1);
	if (is_home)
		ft_putendl_fd(dir, 2);
	msh_env_setvar(env_list, "OLDPWD", curr_dir);
	msh_env_setvar(env_list, "PWD", dir);
	return (0);
}
