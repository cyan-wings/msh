/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_free_t_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:45:23 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 16:45:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_env_free_t_env(void *content)
{
	t_env	*env_var;
	char	*k;
	char	*v;

	env_var = (t_env *) content;
	k = env_var->key;
	v = env_var->val;
	ft_memdel((void **) &k);
	ft_memdel((void **) &v);
	free(content);
	return ;
}