/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_init.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:23:18 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 07:27:33 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_env.h"

static int	check_null_param(t_ast *node, char ***argv_arr,
				t_list *env_list, char ***envp_arr)
{
	if (!node)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
			"node is NULL.");
		return (0);
	}
	if (!argv_arr)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
			"argv_arr is NULL.");
		return (0);
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
			"env_list is NULL.");
		return (0);
	}
	if (!envp_arr)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
			"envp_arr is NULL.");
		return (0);
	}
	return (1);
}

/*
 * Builds the argv for the execve function.
 * First element in the array must be the executable.
 * Note:
 * 		argv is always NULL terminated.
 * 		+ 2 due to the executable and the NULL terminator.
 * 		i is not incremented in the while loop becauase first index
 * 		of the arguments' child array is 0.
 */
static void	get_argv_arr(t_ast *arguments_node, char ***argv_arr)
{
	int		i;

	if (ft_strcmp(arguments_node->type, "arguments"))
		return (msh_perror_exit("debug",
				"msh_execute_simple_cmd_init: get_argv_arr",
				"Node is not arguments.", EXIT_FAILURE));
	*argv_arr = (char **)ft_calloc(arguments_node->child_count + 1,
			sizeof(char *));
	if (!*argv_arr)
		return (msh_perror_exit("msh_execute_simple_cmd_init: get_argv_arr",
				"argv_arr", "malloc fail.", EXIT_FAILURE));
	i = -1;
	while (++i < arguments_node->child_count)
	{
		(*argv_arr)[i] = ft_strdup(arguments_node->children[i]->value);
		if ((*argv_arr)[i] == NULL)
			return (msh_perror_exit("msh_execute_simple_cmd_init: get_argv_arr",
					"argv_arr[i]", "malloc fail.", EXIT_FAILURE));
	}
}

static char	*get_env_var(t_list *env_list)
{
	t_env	*current_env;
	char	*res;
	size_t	key_len;
	size_t	val_len;

	current_env = (t_env *)env_list->content;
	key_len = ft_strlen(current_env->key);
	val_len = ft_strlen(current_env->val);
	res = ft_memalloc(key_len + val_len + 2);
	ft_strlcpy(res, current_env->key, key_len + 1);
	res[key_len] = '=';
	ft_strlcpy(res + key_len + 1, current_env->val, val_len + 1);
	return (res);
}

void	get_envp_arr(t_list **env_list, char ***envp_arr)
{
	int		i;

	*envp_arr = (char **)ft_calloc((ft_lstsize(*env_list) + 1),
			sizeof(char *));
	if (!*envp_arr)
		return (msh_perror_exit("msh_execute_simple_cmd_init: get_envp_arr",
				"envp_arr", "malloc fail.", EXIT_FAILURE));
	i = 0;
	while (*env_list)
	{
		(*envp_arr)[i++] = get_env_var(*env_list);
		*env_list = (*env_list)->next;
	}
}

int	msh_execute_simple_cmd_init(t_ast *node, t_list **env_list,
		char ***envp_arr, char ***argv_arr)
{
	t_redir_st	**redir_st_arr;
	int			status;

	if (!check_null_param(node, argv_arr, env_list, envp_arr))
		return (ERROR);
	get_envp_arr(env_list, envp_arr);
	if (node->children[0]->child_count)
		get_argv_arr(node->children[0], argv_arr);
	status = 0;
	redir_st_arr = NULL;
	if (node->children[1]->child_count)
	{
		status = msh_execute_simple_cmd_redirs(node->children[1],
				&redir_st_arr);
		msh_execute_simple_cmd_redirs_restore(&redir_st_arr);
	}
	return (status);
}
