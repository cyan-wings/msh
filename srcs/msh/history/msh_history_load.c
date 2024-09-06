/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:44:45 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:07:14 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "msh.h"
#include "get_next_line.h"
#include "history.h"
#include "ft_mem_utils.h"

void	msh_perror_exit(char *error_msg, int status);

void	msh_history_load(const char *filename)
{
	int		fd;
	char	*line;

	fd = -1;
	fd = open(filename, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		msh_perror_exit("Open .msh_history", EXIT_FAILURE);
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		add_history(line);
		ft_memdel((void **) &line);
		line = get_next_line(fd);
	}
	close(fd);
	return ;
}
