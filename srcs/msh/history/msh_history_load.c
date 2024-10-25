/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:44:45 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:11:09 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_history_load(const char *filename)
{
	int		fd;
	char	*line;

	if (!filename)
		return (msh_perror_exit("debug", "msh_history_load",
				"filename is NULL.", EXIT_FAILURE));
	fd = -1;
	fd = open(filename, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		return (msh_perror_exit("msh_history_load", HISTORY_FILE,
				strerror(errno), EXIT_FAILURE));
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		add_history(line);
		ft_memdel((void **) &line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
		return (msh_perror_exit("msh_history_load", NULL, strerror(errno),
				EXIT_FAILURE));
	return ;
}
