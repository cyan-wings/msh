/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:36:59 by myeow             #+#    #+#             */
/*   Updated: 2024/10/24 22:03:26 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_print_utils.h"

void	msh_history_load(const char *filename);

char	*msh_input_get(t_list *env_list);

void	msh_input_process(char *input, t_list **env_list);

void	init_msh(t_list **env_list)
{
	signal(SIGQUIT, SIG_IGN);
	msh_env_init(env_list);
	msh_history_load(HISTORY_FILE);
}

//Better to register signal handler before modifying terminal settings.
//system("leaks msh -q");
int	main(void)
{
	t_list		*env_list;
	char		*input;

	env_list = NULL;
	init_msh(&env_list);
	input = NULL;
	while (1)
	{
		signal(SIGINT, msh_signal_ctrl_c);
		msh_signal_conf_term(0);
		input = msh_input_get(env_list);
		if (!input)
		{
			if (isatty(STDERR_FILENO))
				ft_putendl_fd("exit", STDERR_FILENO);
			msh_signal_conf_term(1);
			break ;
		}
		msh_input_process(input, &env_list);
		ft_memdel((void **)&input);
	}
	rl_clear_history();
	msh_env_free(&env_list);
	return (0);
}
