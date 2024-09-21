#ifndef MSH_EXECUTION_H
# define MSH_EXECUTION_H

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

int		msh_execute(t_ast *node, t_list **env_list);

#endif