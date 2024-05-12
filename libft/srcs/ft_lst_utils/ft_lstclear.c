/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:29:46 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:02:15 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_lst_utils.h"

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*tmp;

	if (lst && del)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
	}
}
