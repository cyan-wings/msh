/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_execute.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:27:51 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:12:13 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_env.h"

static int	check_null_param(char **argv_arr, char **envp_arr,
		t_list **env_list)
{
	int	flag;

	flag = 1;
	if (!argv_arr)
	{
		msh_perror("debug", "msh_execute_simple_cmd_execute",
			"argv_arr is NULL.");
		flag = 0;
	}
	if (!envp_arr)
	{
		msh_perror("debug", "msh_execute_simple_cmd_execute",
			"envp_arr is NULL.");
		flag = 0;
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_execute_simple_cmd_execute",
			"env_list is NULL.");
		flag = 0;
	}
	return (flag);
}

static void	signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	msh_signal_conf_term(1);
}

static int	find_path_access(char **path_split, char **argv_arr)
{
	int			i;
	struct stat	s;
	char		*tmp;

	tmp = NULL;
	i = -1;
	while (path_split[++i])
	{
		if (path_split[i][ft_strlen(path_split[i]) - 1] != '/')
			ft_strvappend(&tmp, path_split[i], "/", argv_arr[0], NULL);
		else
			ft_strvappend(&tmp, path_split[i], argv_arr[0], NULL);
		if (!tmp)
			return (msh_perror_exit_int("msh_execute_simple_cmd_execute",
					"find_path_access", "malloc fail.", EXIT_FAILURE));
		if (!access(tmp, F_OK) && (!stat(tmp, &s) && !S_ISDIR(s.st_mode)))
		{
			ft_memdel((void **)&argv_arr[0]);
			argv_arr[0] = tmp;
			return (0);
		}
		ft_memdel((void **)&tmp);
	}
	return (ERROR);
}

static int	search_path(char **argv_arr, t_list **env_list)
{
	char	**path_split;

	path_split = NULL;
	if (argv_arr[0] && argv_arr[0][0])
	{
		path_split = msh_utils_split(msh_env_getvar(*env_list, "PATH"), ':',
				"msh_execute_simple_cmd_path", "get_path_split: path_split");
		if (!find_path_access(path_split, argv_arr))
		{
			ft_free_ft_split(path_split);
			return (0);
		}
	}
	ft_free_ft_split(path_split);
	return (ERROR);
}

int	msh_execute_simple_cmd_execute(char **argv_arr, char **envp_arr,
		t_list **env_list)
{
	int	status;

	if (!check_null_param(argv_arr, envp_arr, env_list))
		return (ERROR);
	signal_reset();
	if (!ft_strchr(argv_arr[0], '/') && msh_env_getvar(*env_list, "PATH"))
	{
		if (search_path(argv_arr, env_list) == ERROR)
		{
			msh_perror(argv_arr[0], NULL, "command not found");
			errno = 0;
			return (127);
		}
	}
	execve(argv_arr[0], argv_arr, envp_arr);
	if (errno == ENOENT)
		status = 127;
	else
		status = 126;
	msh_perror(argv_arr[0], NULL, strerror(errno));
	errno = 0;
	return (status);
}
