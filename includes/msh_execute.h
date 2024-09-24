/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:06:21 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 20:47:43 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXECUTE_H
# define MSH_EXECUTE_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>

# include "ft_lst_utils.h"
# include "ft_mem_utils.h"
# include "ft_string_utils.h"

# include "msh_perror.h"
# include "msh_signal.h"
# include "msh_parse.h"
# include "msh_builtins.h"

typedef enum e_redirection_type
{
    REDIR_IN = 1,
    REDIR_OUT = 2,
    REDIR_HERE = 3,
    REDIR_APP = 4,
}	t_redir_type;

int		msh_execute(t_ast *node, t_list **env_list);

#endif
