/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:39:01 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 16:40:58 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_perror.h"

int	msh_perror_int(char *s1, char *s2, char *msg)
{
	msh_perror(s1, s2, msg);
	return (ERROR);
}
