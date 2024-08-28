/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_redirs.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:21:04 by myeow             #+#    #+#             */
/*   Updated: 2024/08/28 20:31:10 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"

static void	handle_redirection_in(int *fd, t_ast *node)
{
	if (*fd != -69)
	{
		close(*fd);
		*fd = -69;
	}
	if (!ft_strcmp(node->value, "<" ))
		*fd = open(node->children[0]->value, O_RDONLY);
	else
		*fd = open("here_doc", O_RDONLY);
}

static void	handle_redirection_out(int *fd, t_ast *node)
{
	if (*fd != -69)
	{
		close(*fd);
		*fd = -69;
	}
	if (!ft_strcmp(node->value, ">>" ))
		*fd = open(node->children[0]->value,
				O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
	else
		*fd = open(node->children[0]->value,
				O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
}

void	msh_execute_util_dup2(int oldfd, int newfd);

void	msh_execute_simple_cmd_redirs(t_ast *node)
{
	int		i;
	int		in;
	int		out;
	t_ast	*current;

	i = -1;
	in = -69;
	out = -69;
	while (++i <= node->child_count)
	{
		current = node->children[i];
		if (!ft_strcmp(current->value, "<<") || !ft_strcmp(current->value, "<"))
			handle_redirection_in(&in, current);
		else if (!ft_strcmp(current->value, ">")
			|| !ft_strcmp(current->value, ">>"))
			handle_redirection_out(&out, current);
	}
	if (in != -69)
		msh_execute_util_dup2(in, STDIN_FILENO);
	if (out != -69)
		msh_execute_util_dup2(out, STDOUT_FILENO);
}
