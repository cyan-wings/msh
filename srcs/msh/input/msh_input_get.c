/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:55:44 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 15:08:47 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
 * Prompt must be freed.
 */
static char	*create_prompt(t_list *env_list)
{
	char	*user_str;
	char	*pwd_str;
	char	*prompt;
	int		i;

	user_str = msh_env_getvar(env_list, "USER");
	pwd_str = msh_env_getvar(env_list, "PWD");
	prompt = msh_utils_memalloc(ft_strlen(user_str) + ft_strlen(pwd_str) + 6,
			"msh_input_get", "get_prompt");
	ft_memcpy(prompt, user_str, ft_strlen(user_str));
	i = ft_strlen(user_str);
	ft_memcpy(prompt + i++, "@", 1);
	ft_memcpy(prompt + i, pwd_str, ft_strlen(pwd_str));
	i += ft_strlen(pwd_str);
	ft_memcpy(prompt + i, " $> ", 4);
	return (prompt);
}

void	get_prompt(char **prompt, t_list *env_list)
{
	*prompt = msh_env_getvar(env_list, "PS1");
	if (*prompt)
		*prompt = msh_utils_strdup(*prompt, "msh_input_get", NULL);
	else
		*prompt = create_prompt(env_list);
}

void	msh_history_save(char *input, t_list *env_list);

char	*msh_input_get(t_list *env_list)
{
	char	*prompt;
	char	*input;

	if (!env_list)
	{
		msh_perror("debug", "msh_input_get", "env_list is NULL.");
		return (NULL);
	}
	prompt = NULL;
	get_prompt(&prompt, env_list);
	input = NULL;
	if (isatty(STDIN_FILENO))
		input = readline(prompt);
	else
		input = get_next_line(STDIN_FILENO);
	if (!input)
	{
		ft_memdel((void **) &prompt);
		return (NULL);
	}
	else if (isatty(STDIN_FILENO) && *input)
		msh_history_save(input, env_list);
	ft_memdel((void **) &prompt);
	return (input);
}
