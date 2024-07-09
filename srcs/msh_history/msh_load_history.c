/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_load_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:44:45 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:44:47 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <readline/history.h>
#include "get_next_line.h"
#include "msh.h"

void	msh_load_history(const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		msh_perror_exit("Open .msh_history", EXIT_FAILURE);
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
