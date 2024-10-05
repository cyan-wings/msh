#include "msh_execute.h"

int	*msh_execute_exit_status_ptr(void);

void	msh_execute_exit_status_set(int status)
{
	if (status == ERROR)
		status = EXIT_FAILURE;
	*msh_execute_exit_status_ptr() = status;
}