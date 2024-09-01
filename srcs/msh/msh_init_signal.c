/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:05:41 by myeow             #+#    #+#             */
/*   Updated: 2024/09/01 19:06:54 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	sigint_handler(int sig)
{
	if (sig != SIGINT)
    return;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	msh_init_signal(void)
{
	struct termios term;
	
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr\n");
		exit(errno);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr\n");
		exit(errno);
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_DFL);
}
