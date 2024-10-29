/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:36:59 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 15:27:51 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <signal.h>

static char	*set_home_env_var(t_list **env_list)
{
	char	*env_val;

	env_val = NULL;
	env_val = msh_utils_getcwd("init_msh", "set_home_env_var: env_val");
	if (!env_val)
		return (NULL);
	msh_env_setvar(env_list, "HOME", env_val);
	return (env_val);
}

void	msh_history_load(const char *filename);

static int	init_msh(t_list **env_list, char **envp)
{
	char	*tmp;

	signal(SIGQUIT, SIG_IGN);
	msh_env_init(env_list, envp);
	tmp = NULL;
	tmp = msh_env_getvar(*env_list, "HOME");
	if (!tmp)
		tmp = set_home_env_var(env_list);
	else
		tmp = msh_utils_strdup(tmp, "init_msh", "ft_strdup(tmp)");
	if (!tmp)
		return (ERROR);
	ft_strvappend(&tmp, "/", HISTORY_FILE, NULL);
	if (!tmp)
		return (msh_perror_exit_int("init_msh",
				"ft_strvappend(&tmp, /, HISTORY_FILE)",
				"malloc fail.", EXIT_FAILURE));
	msh_history_load(tmp);
	msh_env_setvar(env_list, "MSH_HIST_FILE", tmp);
	ft_memdel((void **)&tmp);
	return (0);
}

char	*msh_input_get(t_list *env_list);

void	msh_input_process(char *input, t_list **env_list);

void	msh_routine(t_list *env_list, char *input)
{
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
			return ;
		}
		signal(SIGINT, SIG_IGN);
		errno = 0;
		msh_input_process(input, &env_list);
		ft_memdel((void **)&input);
	}
}

int	main(int argc __attribute((unused)), char **argv __attribute((unused)),
		char **envp)
{
	t_list		*env_list;
	char		*input;

	env_list = NULL;
	if (init_msh(&env_list, envp) == ERROR)
		return (1);
	input = NULL;
	msh_routine(env_list, input);
	rl_clear_history();
	msh_env_free(&env_list);
	return (0);
}
