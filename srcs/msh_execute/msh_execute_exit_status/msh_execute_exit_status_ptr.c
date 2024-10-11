/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_exit_status_ptr.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:15:52 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 07:15:54 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*msh_execute_exit_status_ptr(void)
{
	static int	last_exit_status = 0;

	return (&last_exit_status);
}
