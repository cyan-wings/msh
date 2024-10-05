#include "msh_execute.h"

void	msh_execute_free(char **argv_arr, char **envp_arr);

void	msh_execute_free_exit(int status, char **argv_arr, char **envp_arr)
{
	msh_execute_free(argv_arr, envp_arr);
	exit(status);
}