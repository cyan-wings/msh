/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_token_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:45:24 by myeow             #+#    #+#             */
/*   Updated: 2024/07/03 20:03:44 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_print_token_list(t_list *token_list)
{
	ft_putstr_fd("Tokens:\n\t\t", 1);
	while (token_list)
	{
		ft_putchar_fd('[', 1);
		ft_putstr_fd(((t_token *) token_list->content)->value, 1);
		ft_putchar_fd(']', 1);
		ft_putstr_fd(" -> ", 1);
		token_list = token_list->next;
	}
	ft_putstr_fd("NULL\n", 1);
	return ;
}
