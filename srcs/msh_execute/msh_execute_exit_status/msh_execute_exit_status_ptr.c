int	*msh_execute_exit_status_ptr(void)
{
	static int	last_exit_status = 0;

	return (&last_exit_status);
}