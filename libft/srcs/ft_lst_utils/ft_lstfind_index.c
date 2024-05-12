/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:28:39 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:02:16 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst_utils.h"

/*
 * Returns the index of "n" where it was first found
 */
int	ft_lstfind_index(t_list *lst, int n)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (*(int *)lst->content == n)
			return (i);
		lst = lst->next;
		++i;
	}
	return (-1);
}
