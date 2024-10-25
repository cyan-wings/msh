/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:44:37 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:11:21 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"

static int	check_null_param(char *input, t_list *env_list)
{
	int	flag;

	flag = 1;
	if (!input)
	{
		msh_perror("debug", "msh_history_save", "input is NULL.");
		flag = 0;
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_history_save", "env_list is NULL.");
		flag = 0;
	}
	return (flag);
}

void	msh_history_save(char *input, t_list *env_list)
{
	int		fd;
	char	*filename;
	ssize_t	input_len;

	if (!check_null_param(input, env_list))
		return ;
	add_history(input);
	filename = msh_env_getvar(env_list, "MSH_HIST_FILE");
	if (!filename)
		return (msh_perror_exit("debug", "msh_history_save",
				"MSH_HIST_FILE is not set", EXIT_FAILURE));
	fd = open(filename, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		msh_perror_exit("msh_history_save", HISTORY_FILE,
			strerror(errno), EXIT_FAILURE);
	input_len = ft_strlen(input);
	if (write(fd, input, input_len) != input_len || write(fd, "\n", 1) != 1)
		msh_perror("msh_history_save", NULL, "Write to history error.");
	if (close(fd) == -1)
		return (msh_perror_exit("msh_history_save", NULL, strerror(errno),
				EXIT_FAILURE));
	return ;
}
