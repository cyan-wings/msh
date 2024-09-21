#include "msh.h"
#include <signal.h>

void	msh_signal_ctrl_c(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}