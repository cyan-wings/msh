/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:35:26 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:02:22 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst_utils.h"

/*
 * Takes the top item from lst_a and places it on top of lst_b.
 */
void	ft_lstpush(t_list **lst_a, t_list **lst_b)
{
	t_list	*temp;

	if (!lst_a || !*lst_a)
		return ;
	temp = *lst_b;
	*lst_b = *lst_a;
	*lst_a = (*lst_a)->next;
	(*lst_b)->next = temp;
}
