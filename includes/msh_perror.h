/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:07:47 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 17:34:01 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PERROR_H
# define MSH_PERROR_H

# include <errno.h>

# define ERROR -1

void	msh_perror(char *s1, char *s2, char *msg);
int		msh_perror_int(char *s1, char *s2, char *msg);
void	msh_perror_exit(char *s1, char *s2, char *msg, int status);
int		msh_perror_exit_int(char *s1, char *s2, char *msg, int status);

#endif
