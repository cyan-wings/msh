/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_save_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:44:37 by myeow             #+#    #+#             */
/*   Updated: 2024/08/27 16:32:58 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "msh.h"
#include "ft_string_utils.h"

void	msh_save_history(char *input, const char *filename)
{
	int		fd;
	ssize_t	input_len;

	add_history(input);
	fd = open(filename, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		msh_perror_exit("Open history when save", EXIT_FAILURE);
	input_len = ft_strlen(input);
	if (write(fd, input, input_len) != input_len || write(fd, "\n", 1) != 1)
		perror("Write to history");
	close(fd);
	return ;
}
