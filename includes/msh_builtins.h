/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:05:10 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 14:55:55 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BUILTINS_H
# define MSH_BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include "ft_lst_utils.h"
# include "ft_char_utils.h"
# include "ft_mem_utils.h"
# include "ft_string_utils.h"
# include "ft_print_utils.h"

# include "msh_perror.h"
# include "msh_utils.h"

typedef int	(*t_bif)(int argc, char **argv, t_list **env_list,
			int subshell_flag);

t_bif	*msh_builtins_get_builtin(char *executable);

#endif
