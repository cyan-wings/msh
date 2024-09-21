/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:44:37 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 15:11:16 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"

static int	check_null_param(char *input, const char *filename)
{
	int	flag;

	flag = 1;
	if (!input)
	{
		msh_perror("debug", "msh_history_save", "input is NULL.");
		flag = 0;
	}
	if (!filename)
	{
		msh_perror("debug", "msh_history_save", "filename is NULL.");
		flag = 0;
	}
	return (flag);
}

void	msh_history_save(char *input, const char *filename)
{
	int		fd;
	ssize_t	input_len;

	if (!check_null_param(input, filename))
		return ;
	add_history(input);
	fd = open(filename, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		msh_perror_exit("msh_history_save", HISTORY_FILE,
			strerror(errno), EXIT_FAILURE);
	input_len = ft_strlen(input);
	if (write(fd, input, input_len) != input_len || write(fd, "\n", 1) != 1)
		msh_perror("msh_history_save", NULL, "Write to history error.");
	close(fd);
	return ;
}
