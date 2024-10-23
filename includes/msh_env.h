/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:05:21 by myeow             #+#    #+#             */
/*   Updated: 2024/10/23 16:36:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ENV_H
# define MSH_ENV_H

# include <stdlib.h>
# include <unistd.h>

# include "ft_lst_utils.h"
# include "ft_mem_utils.h"
# include "ft_string_utils.h"
# include "ft_print_utils.h"

# include "msh_perror.h"

typedef struct s_environment_variable
{
	char		*key;
	char		*val;
}	t_env;

void	msh_env_init(t_list **env_list);
void	msh_env_setvar(t_list **env_list, char *k, char *v);
char	*msh_env_getvar(t_list *env_list, char *k);
void	msh_env_delvar(t_list **env_list, char *k);
void	msh_env_print(t_list *env_list, int export_flag);
void	msh_env_free(t_list **env_list);

#endif
