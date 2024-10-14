/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 07:58:35 by myeow             #+#    #+#             */
/*   Updated: 2024/10/07 07:59:08 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

void	msh_execute_free(char **argv_arr, char **envp_arr)
{
	if (argv_arr)
		ft_free_ft_split(argv_arr);
	if (envp_arr)
		ft_free_ft_split(envp_arr);
}
