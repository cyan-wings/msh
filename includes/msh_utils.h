/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:32:24 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 17:46:18 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_UTILS_H
# define MSH_UTILS_H

char	*msh_utils_strdup(char *str, char *msg1, char *msg2);
void	*msh_utils_memalloc(size_t size, char *msg1, char *msg2);
char	*msh_utils_getcwd(char *msg1, char *msg2);
int		msh_utils_arraylen(char **array);
void	msh_utils_strrpad(char **strptr, char padding);
char	**msh_utils_split(char *str, char c, char *msg1, char *msg2);

#endif
