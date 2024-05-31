/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_save_history.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:50:20 by myeow             #+#    #+#             */
/*   Updated: 2024/05/27 00:48:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <readline/history.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "ft_string_utils.h"

void	minishell_save_history(char *input, const char *filename)
{
	int		fd;
	ssize_t	input_len;

	add_history(input);
	fd = open(filename, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		minishell_perror_exit("Open history when save", EXIT_FAILURE);
	input_len = ft_strlen(input);
	if (write(fd, input, input_len) != input_len || write(fd, "\n", 1) != 1)
		perror("Write to history");
	close(fd);
	return ;
}
