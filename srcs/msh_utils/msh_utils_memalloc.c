/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils_memalloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:27:43 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:13:33 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"
#include "msh_perror.h"
#include <stdlib.h>

void	*msh_utils_memalloc(size_t size, char *msg1, char *msg2)
{
	void	*out;

	out = NULL;
	out = ft_memalloc(size);
	if (!out)
		msh_perror_exit(msg1, msg2, "malloc fail.", EXIT_FAILURE);
	return (out);
}
