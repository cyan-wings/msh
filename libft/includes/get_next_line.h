/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:34:21 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:50:31 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include "ft_mem_utils.h"
# include "ft_string_utils.h"

# if defined(__linux__)
#  define OPEN_MAX 256
# endif

char	*ft_strjoin_read(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
