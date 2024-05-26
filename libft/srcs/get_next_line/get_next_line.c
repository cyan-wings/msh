/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:37:49 by myeow             #+#    #+#             */
/*   Updated: 2024/05/26 23:46:00 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_readline(char *str, int fd)
{
	void	*buffer;
	int		read_bytes;

	if (!str)
		str = ft_calloc(1, sizeof(char));
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (0);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (0);
		}
		*((char *) buffer + read_bytes) = 0;
		str = ft_strjoin_read(str, buffer);
	}
	free(buffer);
	return (str);
}

/*
 * Modified for minishell.
 */
static char	*ft_extractline(char *str)
{
	size_t	i;
	char	*new_str;

	if (!*str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		++i;
	new_str = ft_calloc(i + 1, sizeof(char));
	if (!new_str)
		return (0);
	i = -1;
	while (*str && *str != '\n')
		new_str[++i] = *str++;
	return (new_str);
}

static char	*get_leftover_line(char *str)
{
	char	*str_cpy;
	char	*leftover_str;
	char	*leftover_str_cpy;

	str_cpy = str;
	while (*str_cpy && *str_cpy != '\n')
		++str_cpy;
	if (!(*str_cpy))
	{
		free(str);
		return (0);
	}
	leftover_str = ft_calloc(ft_strlen(++str_cpy) + 1, sizeof(char));
	if (!leftover_str)
		return (0);
	leftover_str_cpy = leftover_str;
	while (*str_cpy)
		*leftover_str++ = *str_cpy++;
	free(str);
	return (leftover_str_cpy);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*next_line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	buffer[fd] = ft_readline(buffer[fd], fd);
	if (!buffer[fd])
		return (0);
	next_line = ft_extractline(buffer[fd]);
	buffer[fd] = get_leftover_line(buffer[fd]);
	return (next_line);
}
