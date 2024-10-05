#include "msh_execute.h"

void	msh_execute_free(char **argv_arr, char **envp_arr)
{
    if (argv_arr)
        ft_free_ft_split(argv_arr);
    if (envp_arr)
	    ft_free_ft_split(envp_arr);
	rl_clear_history();
}