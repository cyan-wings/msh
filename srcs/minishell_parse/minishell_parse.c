/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:33:55 by myeow             #+#    #+#             */
/*   Updated: 2024/07/04 17:43:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_parse(t_list *token_list, t_ast **root)
{
	if (!minishell_parse_token(token_list))
		return (0);
	else
		ft_putendl_fd("Parsing token success!", 1);
	*root = minishell_parse_pipeline(&token_list);
	return (1);
}
