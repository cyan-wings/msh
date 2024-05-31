/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_token_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:17:12 by myeow             #+#    #+#             */
/*   Updated: 2024/05/31 13:18:46 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_print_token_list(t_list *token_list)
{
	while (token_list)
	{
		ft_putstr_fd(((t_token *) token_list->content)->string, 1);
		ft_putchar_fd('\n', 1);
		token_list = token_list->next;
	}
	return ;
}
