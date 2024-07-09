/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:37:55 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:38:19 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "msh.h"
#include "ft_mem_utils.h"
#include "ft_string_utils.h"

/*
 * Prompt must be freed.
 */
char	*msh_prompt(t_list *env_list)
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
