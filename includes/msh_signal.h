#ifndef MSH_SIGNAL_H
# define MSH_SIGNAL_H

# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <signal.h>

# include "msh_perror.h"

void	msh_signal_ctrl_c(int sig);
void	msh_signal_conf_term(int echo_ctrl_chr_flag);

#endif