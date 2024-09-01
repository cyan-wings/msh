/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:14:55 by myeow             #+#    #+#             */
/*   Updated: 2024/09/01 19:17:53 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_execute_simple_cmd_redirs(t_ast *node);

char	*generate_filepath(char *command, char *path)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(path, "/");
	res = ft_strjoin(temp, command);
	free(temp);
	return (res);
}

//get ARGUMENTS FOR EXECVE
static char	**get_var_arr(t_ast *node)
{
	int		i;
	char	**res;
	t_ast	*current;

	current = node->children[1];
	if (ft_strcmp(current->type, "arguments"))
		return (NULL);
	i = -1;
	res = (char **)malloc(sizeof(char *) * (current->child_count + 2));
	res[0] = ft_strdup(node->children[0]->value);
	while (++i < current->child_count)
		res[i + 1] = ft_strdup(current->children[i]->value);
	res[i + 1] = NULL;
	return (res);
}

static void	signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	run_execve(t_ast *node, t_list **env_list)
{
	int		i;
	char	**path;
	char	*filepath;
	int		res;
	char	**argv_arr;
	char	**envp_arr;

	i = -1;
	signal_reset();
	path = ft_split(msh_env_getvar(*env_list, "PATH"), ':');
	argv_arr = get_var_arr(node);
	envp_arr = msh_env_get_array(*env_list);
	while (path[++i])
	{
		filepath = generate_filepath(node->children[0]->value, path[i]);
		// printf("current filepath: %s\n\n", filepath);
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
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

void	msh_execute_simple_cmd(t_ast *node, t_list **env_list)
{
	t_bif	*builtin_func;

	if (node->children[2]->child_count > 0)
		msh_execute_simple_cmd_redirs(node->children[2]);
	builtin_func = msh_builtins_get_builtin(node->children[0]->value);
	if (builtin_func)
		exit((*builtin_func)(1, get_var_arr(node), env_list, 1));
	else
		run_execve(node, env_list);
}
