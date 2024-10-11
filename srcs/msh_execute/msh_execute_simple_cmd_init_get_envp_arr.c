/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_init_get_envp_arr.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 00:41:07 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 07:22:56 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

static int	get_env_list_len(t_list *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		env_list = env_list->next;
		i++;
	}
	return (++i);
}

static char	*get_current_var(t_list *env_list)
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

/*
 * env_list must be converted into an array to run execve.
 * TODO: Make this return void.
 */
void	msh_execute_simple_cmd_init_get_envp_arr(t_list *env_list,
		char ***envp_arr)
{
	int		i;

	if (!envp_arr)
		msh_perror_exit("debug", "msh_execute_simple_cmd_get_envp_arr",
			"envp_arr is NULL", EXIT_FAILURE);
	*envp_arr = (char **)ft_calloc((get_env_list_len(env_list) + 1),
			sizeof(char *));
	if (!*envp_arr)
		return (msh_perror_exit("msh_execute_simple_cmd_get_envp_arr",
				"envp_arr", "malloc fail.", EXIT_FAILURE));
	i = 0;
	while (env_list)
	{
		(*envp_arr)[i++] = get_current_var(env_list);
		env_list = env_list->next;
	}
}
