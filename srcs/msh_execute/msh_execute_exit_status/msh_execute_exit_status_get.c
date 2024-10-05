int	*msh_execute_exit_status_ptr(void);

int	msh_execute_exit_status_get(void)
{
	return (*msh_execute_exit_status_ptr());
}