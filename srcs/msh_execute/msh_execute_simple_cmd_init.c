/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_init.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:23:18 by myeow             #+#    #+#             */
/*   Updated: 2024/10/30 17:53:41 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_env.h"

static int	check_null_param(t_ast *node, t_list **env_list,
				char ***envp_arr, char ***argv_arr)
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

static char	*get_env_var(t_list *env_list)
{
	t_env	*current_env;
	char	*res;
	size_t	key_len;
	size_t	val_len;

	current_env = (t_env *)env_list->content;
	key_len = ft_strlen(current_env->key);
	val_len = ft_strlen(current_env->val);
	res = msh_utils_memalloc(key_len + val_len + 2,
			"msh_execute_simple_cmd_init", "get_env_var");
	ft_strlcpy(res, current_env->key, key_len + 1);
	res[key_len] = '=';
	ft_strlcpy(res + key_len + 1, current_env->val, val_len + 1);
	return (res);
}

void	get_envp_arr(t_list **env_list, char ***envp_arr)
{
	int		i;
	t_list	*curr;

	*envp_arr = (char **)ft_calloc((ft_lstsize(*env_list) + 1),
			sizeof(char *));
	if (!*envp_arr)
		return (msh_perror_exit("msh_execute_simple_cmd_init: get_envp_arr",
				"envp_arr", "malloc fail.", EXIT_FAILURE));
	i = 0;
	curr = *env_list;
	while (curr)
	{
		(*envp_arr)[i++] = get_env_var(curr);
		curr = curr->next;
	}
}

void	msh_execute_simple_cmd_init_get_argv_arr(t_ast *arguments_node,
				char ***argv_arr, t_list **env_list);

/*
 * 	Process:
 * 		(1) Obtain the argv array which requires expansion.
 * 		(2) Perform redirections and restore them back as a test for errors.
 */
int	msh_execute_simple_cmd_init(t_ast *node, t_list **env_list,
		char ***envp_arr, char ***argv_arr)
{
	t_redir_st	**redir_st_arr;
	int			status;

	if (!check_null_param(node, env_list, envp_arr, argv_arr))
		return (ERROR);
	get_envp_arr(env_list, envp_arr);
	if (node->children[0]->child_count)
		msh_execute_simple_cmd_init_get_argv_arr(node->children[0], argv_arr,
			env_list);
	status = 0;
	redir_st_arr = NULL;
	if (node->children[1]->child_count)
	{
		status = msh_execute_simple_cmd_redirs(node->children[1],
				&redir_st_arr, env_list);
		msh_execute_simple_cmd_redirs_restore(&redir_st_arr);
	}
	return (status);
}
