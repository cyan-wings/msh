/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:36:19 by myeow             #+#    #+#             */
/*   Updated: 2024/08/28 20:38:15 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	signal_init(void)
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

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
    return;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	msh_signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
