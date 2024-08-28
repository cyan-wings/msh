/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:14:55 by myeow             #+#    #+#             */
/*   Updated: 2024/08/28 19:45:13 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_execute_simple_cmd_redirs(t_ast *node);

void	reset_signal(void);

char	*generate_filepath(char *command, char *path)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(path, "/");
	res = ft_strjoin(temp, command);
	free(temp);
	return (res);
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
	reset_signal();
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

void	msh_execute_simple_cmd(t_ast *node, t_list **env_list,
		t_bif *builtin_list)
{
	if (node->children[2]->child_count > 0)
		msh_execute_simple_cmd_redirs(node->children[2]);
	if (check_is_plugin(node->children[0]->value))
		exit(builtin_list[0](node, env_list));
	else
		run_execve(node, env_list);
}
