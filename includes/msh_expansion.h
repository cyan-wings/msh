#ifndef MSH_EXPANSION_H
# define MSH_EXPANSION_H

#include <unistd.h>

#include "ft_lst_utils.h"
#include "ft_mem_utils.h"
#include "ft_string_utils.h"
#include "ft_print_utils.h"

# include "msh_perror.h"
# include "msh_env.h"
# include "msh_parse.h"

void	msh_expansion(t_ast *node, t_list *env_list);
void	msh_expansion_utils_strappend(char **strptr, int start, int i,
			char **new_strptr);

#endif