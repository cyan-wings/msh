/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:37:52 by myeow             #+#    #+#             */
/*   Updated: 2024/05/29 16:59:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "ft_mem_utils.h"
#include "ft_string_utils.h"

/*
 * Prompt must be freed.
 */
char	*minishell_prompt(t_list *env_list)
{
	char	*user_str;
	char	*pwd_str;
	char	*prompt;
	int		i;

	user_str = minishell_env_getvar(env_list, "USER");
	pwd_str = minishell_env_getvar(env_list, "PWD");
	prompt = ft_memalloc(ft_strlen(user_str) + ft_strlen(pwd_str) + 6);
	if (!prompt)
		minishell_perror_exit("Prompt memalloc", EXIT_FAILURE);
	ft_memcpy(prompt, user_str, ft_strlen(user_str));
	i = ft_strlen(user_str);
	ft_memcpy(prompt + i++, "@", 1);
	ft_memcpy(prompt + i, pwd_str, ft_strlen(pwd_str));
	i += ft_strlen(pwd_str);
	ft_memcpy(prompt + i, " $> ", 4);
	return (prompt);
}

