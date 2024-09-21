/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:06:53 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 15:06:56 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
