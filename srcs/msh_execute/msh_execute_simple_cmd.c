/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:14:55 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 21:40:42 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

void	msh_execute_simple_cmd_redirs(t_ast *node);

/*
 * Builds the argv for the execve function.
 * First element in the array must be the executable.
 * Note:
 * 		argv is always NULL terminated.
 * 		+ 2 due to the executable and the NULL terminator.
 * 		i is not incremented in the while loop becauase first index
 * 		of the arguments' child array is 0.
 */
static void	get_argv_arr(t_ast *node, char ***argv_arr)
{
	int		i;
	t_ast	*arguments;

	arguments = node->children[0];
	if (ft_strcmp(arguments->type, "arguments"))
		msh_perror_exit("debug", "msh_execute_simple_cmd: get_argv_arr",
			"Node is not arguments.", EXIT_FAILURE);
	*argv_arr = (char **)ft_calloc(arguments->child_count + 1, sizeof(char *));
	if (!*argv_arr)
		return (msh_perror_exit("get_argv_arr", "argv_arr",
				"malloc fail.", EXIT_FAILURE));
	i = -1;
	while (++i < arguments->child_count)
	{
		(*argv_arr)[i] = ft_strdup(arguments->children[i]->value);
		if ((*argv_arr)[i] == NULL)
			return (msh_perror_exit("get_argv_arr", "argv",
					"malloc fail.", EXIT_FAILURE));
	}
}

char	**msh_execute_simple_cmd_get_envp_arr(t_list *env_list);

static void	signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char	*generate_filepath(char *command, char *path)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(path, "/");
	res = ft_strjoin(temp, command);
	free(temp);
	return (res);
}

/*
 * TODO: rename ft_free_ft_split to be more generic.
 */
static void	run_execve(t_ast *node, t_list **env_list,
		char **argv_arr, char **envp_arr)
{
	int		i;
	char	**path;
	char	*filepath;
	int		res;

	i = -1;
	signal_reset();
	path = ft_split(msh_env_getvar(*env_list, "PATH"), ':');
	while (path[++i])
	{
		filepath = generate_filepath(node->children[0]->value, path[i]);
		res = execve(filepath, argv_arr, envp_arr);
		free(filepath);
		if (res != -1)
			break ;
	}
	if (!path[i])
	{
		perror("Command not found");
		exit(127);
	}
	ft_free_ft_split(path);
}

/*
 * TODO: Fix the builtin_func taking the subshell flag.
 */
int	msh_execute_simple_cmd(t_ast *node, t_list **env_list)
{
	char	**argv_arr;
	char	**envp_arr;
	t_bif	*builtin_func;

	if (node->children[2]->child_count > 0)
		msh_execute_simple_cmd_redirs(node->children[2]);
	argv_arr = 0;
	get_argv_arr(node, &argv_arr);
	envp_arr = msh_execute_simple_cmd_get_envp_arr(*env_list);
	builtin_func = msh_builtins_get_builtin(node->children[0]->value);
	if (builtin_func)
		(*builtin_func)(node->children[1]->child_count + 1,
				argv_arr, env_list, 1);
	else
		run_execve(node, env_list, argv_arr, envp_arr);
	ft_free_ft_split(argv_arr);
	ft_free_ft_split(envp_arr);
	return (0);
}
