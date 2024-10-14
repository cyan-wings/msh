/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_free_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 07:59:22 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 08:04:31 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

void	msh_execute_free(char **argv_arr, char **envp_arr);

void	msh_execute_free_exit(int status, char **argv_arr, char **envp_arr)
{
	msh_execute_free(argv_arr, envp_arr);
	rl_clear_history();
	exit(status);
}
