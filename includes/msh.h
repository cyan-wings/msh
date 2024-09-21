/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:31:55 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 15:06:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "ft_lst_utils.h"
# define HISTORY_FILE ".msh_history"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# ifdef ARCH_X86_64
#  include "readline.h"
#  include "history.h"
# else
#  include <readline.h>
#  include <history.h>
# endif

# include "libft.h"
# include "ft_mem_utils.h"
# include "ft_string_utils.h"
# include "ft_print_utils.h"
# include "get_next_line.h"

# include "msh_perror.h"
# include "msh_signal.h"
# include "msh_env.h"

/*
# define OA "<"
# define CA ">"
# define DOA "<<"
# define DCA ">>"
# define PIPE "|"
# define OP "("
# define CP ")"
# define AND "&&"
# define OR "||"
*/

#endif
