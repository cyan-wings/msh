/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_func_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:48:25 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 15:34:21 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "msh_env.h"
#include "msh_builtins.h"

static int	print_invalid_argument(char *arg_str)
{
	char	*tmp;

	tmp = NULL;
	tmp = msh_utils_memalloc(3, "msh_builtins_func_cd",
			"print_invalid_argument");
	if (!tmp)
		return (msh_perror_exit_int("msh_builtins_func_cd",
				"print_invalid_argument", "malloc fail.", EXIT_FAILURE));
	tmp[0] = arg_str[0];
	tmp[1] = arg_str[1];
	msh_perror("cd", tmp, "invalid option\ncd: usage: cd [dir, -]");
	ft_memdel((void **)&tmp);
	return (1);
}

/*
 * If cd to OLDPWD, the directory must be printed.
 * Hence, we return the flag as true.
 */
static int	get_dir(int argc, char **argv, t_list **env_list, char **dir)
{
	if (argc == 1 || !argv[1] || !*argv[1] || !ft_strcmp(argv[1], "--"))
	{
		*dir = msh_env_getvar(*env_list, "HOME");
		if (!*dir)
			msh_perror("cd", NULL, "HOME not set");
	}
	else if (argv[1] && !ft_strcmp(argv[1], "-"))
	{
		*dir = msh_env_getvar(*env_list, "OLDPWD");
		if (!*dir)
			msh_perror("cd", NULL, "OLDPWD not set");
		return (1);
	}
	else if (argv[1] && argv[1][0] == '-' && argv[1][1])
		return (print_invalid_argument(argv[1]));
	else
		*dir = argv[1];
	return (0);
}

static int	get_change_dir_exit_status(char *dir)
{
	struct stat	statbuf;

	if (access(dir, F_OK))
		return (msh_perror_int("cd", dir, strerror(errno)));
	if (stat(dir, &statbuf))
		return (msh_perror_int("cd", dir, strerror(errno)));
	if (!S_ISDIR(statbuf.st_mode))
		return (msh_perror_int("cd", dir, "Not a directory"));
	if (!(statbuf.st_mode & S_IXUSR))
		return (msh_perror_int("cd", dir, "Permission denied"));
	if (chdir(dir) == -1)
		return (msh_perror_int("cd", "chdir", strerror(errno)));
	return (0);
}

//curr_dir should not be freed since it will be used as an env_val.
static void	update_pwd_env(char *dir, t_list **env_list)
{
	if (dir[0] == '/')
		dir = msh_utils_strdup(dir, "msh_builtins_func_cd", "update_pwd_env");
	else
		dir = msh_utils_getcwd("msh_builtins_func_cd", "update_pwd_env");
	msh_env_setvar(env_list, "PWD", dir);
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
		int argc,
		char **argv, t_list **env_list,
		int subshell_flag __attribute((unused))
)
{
	char		*dir;
	int			print_oldpwd_flag;
	char		*curr_dir;

	dir = NULL;
	print_oldpwd_flag = get_dir(argc, argv, env_list, &dir);
	if (!dir)
		return (EXIT_FAILURE);
	dir = msh_utils_strdup(dir, "msh_builtins_func_cd", "dir");
	curr_dir = NULL;
	curr_dir = msh_utils_getcwd("msh_builtins_func_cd", "curr_dir");
	if (get_change_dir_exit_status(dir) == ERROR)
		return (1);
	if (print_oldpwd_flag)
		ft_putendl_fd(dir, STDOUT_FILENO);
	msh_env_setvar(env_list, "OLDPWD", curr_dir);
	update_pwd_env(dir, env_list);
	ft_memdel((void **)&dir);
	return (0);
}
