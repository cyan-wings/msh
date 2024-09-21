#include <string.h>
#include "msh_signal.h"

void	msh_signal_conf_term(int echo_ctrl_chr_flag)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		msh_perror_exit("msh", "tcgetattr", strerror(errno), EXIT_FAILURE);
	if (echo_ctrl_chr_flag)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		msh_perror_exit("msh", "tcsetattr", strerror(errno), EXIT_FAILURE);
}