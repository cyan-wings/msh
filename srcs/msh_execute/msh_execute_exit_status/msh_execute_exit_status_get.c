/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_exit_status_get.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:16:05 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 07:16:09 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*msh_execute_exit_status_ptr(void);

int	msh_execute_exit_status_get(void)
{
	return (*msh_execute_exit_status_ptr());
}
