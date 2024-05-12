/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:26:45 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:04:33 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
 * Pair this with ft_lstclear.
 */
void	ft_memclear(void *content)
{
	free(content);
	return ;
}
