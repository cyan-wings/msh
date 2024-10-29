/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_conf_term.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:24:36 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 15:24:38 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "msh_signal.h"
#include <stdio.h>

/*
 * This function configures the terminal whether to print a CTRL character.
 */
void	msh_signal_conf_term(int echo_ctrl_chr_flag)
{
	struct termios	term;

	if (!isatty(STDIN_FILENO))
		return ;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		msh_perror_exit("tcgetattr", NULL, strerror(errno), EXIT_FAILURE);
	if (echo_ctrl_chr_flag)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		msh_perror_exit("tcsetattr", NULL, strerror(errno), EXIT_FAILURE);
}
