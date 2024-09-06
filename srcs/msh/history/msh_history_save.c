/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:44:37 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:07:42 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include <fcntl.h>
#include "msh.h"
#include <stdlib.h>
#include "ft_string_utils.h"
#include <unistd.h>

void	msh_history_save(char *input, const char *filename)
{
	int		fd;
	ssize_t	input_len;

	add_history(input);
	fd = open(filename, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		msh_perror_exit("Open history when save", EXIT_FAILURE);
	input_len = ft_strlen(input);
	if (write(fd, input, input_len) != input_len || write(fd, "\n", 1) != 1)
		msh_perror("Write to history error.");
	close(fd);
	return ;
}
