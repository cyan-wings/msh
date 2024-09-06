/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:55:44 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 17:57:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "readline.h"
#include "ft_mem_utils.h"
#include "ft_string_utils.h"
#include <stdlib.h>

/*
 * Prompt must be freed.
 */
static char	*get_prompt(t_list *env_list)
{
	char	*user_str;
	char	*pwd_str;
	char	*prompt;
	int		i;

	user_str = msh_env_getvar(env_list, "USER");
	pwd_str = msh_env_getvar(env_list, "PWD");
	prompt = ft_memalloc(ft_strlen(user_str) + ft_strlen(pwd_str) + 6);
	if (!prompt)
		msh_perror_exit("Prompt memalloc", EXIT_FAILURE);
	ft_memcpy(prompt, user_str, ft_strlen(user_str));
	i = ft_strlen(user_str);
	ft_memcpy(prompt + i++, "@", 1);
	ft_memcpy(prompt + i, pwd_str, ft_strlen(pwd_str));
	i += ft_strlen(pwd_str);
	ft_memcpy(prompt + i, " $> ", 4);
	return (prompt);
}

void	msh_history_save(char *input, const char *filename);

char	*msh_input_get(t_list *env_list)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt(env_list);
	input = readline(prompt);
	if (!input)
		return (NULL);
	if (*input)
		msh_history_save(input, HISTORY_FILE);
	ft_memdel((void **) &prompt);
	return (input);
}
