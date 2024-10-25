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

//When getcwd is given NULL ptr, it dynamically allocates memmory.
//ft_strdup(env_val) is for the history file
static char	*set_home_env_var(t_list **env_list)
{
	char	*env_key;
	char	*env_val;

	env_key = NULL;
	env_key = msh_utils_strdup("HOME", "init_msh",
			"set_home_env_var: env_key");
	env_val = NULL;
	env_val = msh_utils_getcwd("init_msh", "set_home_env_var: env_val");
	msh_env_setvar(env_list, env_key, env_val);
	env_val = msh_utils_strdup(env_val, "init_msh",
			"set_home_env_var: env_val");
	return (env_val);
}

void	msh_history_load(const char *filename);

static void	set_history_file_env_var(t_list **env_list, char *filename)
{
	char	*env_key;
	char	*env_val;

	env_key = NULL;
	env_key = msh_utils_strdup("MSH_HIST_FILE", "init_msh",
			"set_history_file_env_var: env_key");
	env_val = NULL;
	env_val = msh_utils_strdup(filename, "init_msh",
			"set_history_file_env_var: env_key");
	msh_env_setvar(env_list, env_key, env_val);
}

static void	init_msh(t_list **env_list)
{
	char	*tmp;

	signal(SIGQUIT, SIG_IGN);
	msh_env_init(env_list);
	tmp = NULL;
	tmp = msh_env_getvar(*env_list, "HOME");
	if (!tmp)
		tmp = set_home_env_var(env_list);
	else
		tmp = msh_utils_strdup(tmp, "init_msh", "ft_strdup(tmp)");
	ft_strvappend(&tmp, "/", HISTORY_FILE, NULL);
	if (!tmp)
		return (msh_perror_exit("init_msh",
				"ft_strvappend(&tmp, /, HISTORY_FILE)",
				"malloc fail.", EXIT_FAILURE));
	msh_history_load(tmp);
	set_history_file_env_var(env_list, tmp);
	ft_memdel((void **)&tmp);
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

//Better to register signal handler before modifying terminal settings.
//system("leaks msh -q");
int	main(void)
{
	t_list		*env_list;
	char		*input;

	env_list = NULL;
	init_msh(&env_list);
	input = NULL;
	msh_routine(env_list, input);
	rl_clear_history();
	msh_env_free(&env_list);
	return (0);
}
