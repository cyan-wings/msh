#ifndef MSH_BUILTINS_H
# define MSH_BUILTINS_H

# include <unistd.h>
# include <stdlib.h>

# include "ft_lst_utils.h"
# include "ft_char_utils.h"
# include "ft_mem_utils.h"
# include "ft_string_utils.h"
# include "ft_print_utils.h"

# include "msh_perror.h"

typedef int	(*t_bif)(int argc, char **argv, t_list **env_list,
			int subshell_flag);

t_bif	*msh_builtins_get_builtin(char *executable);

#endif