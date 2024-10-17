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

//When getcwd is given NULL ptr, it dynamically allocates memmory.
//ft_strdup(env_val) is for the history file
static char	*set_home_env_var(t_list **env_list)
{
	char	*env_key;
	char	*env_val;

	env_key = NULL;
	env_key = ft_strdup("HOME");
	if (!env_key)
		msh_perror_exit("init_msh",
			"set_home_env_var: env_key",
			"malloc fail.", EXIT_FAILURE);
	env_val = NULL;
	env_val = getcwd(NULL, 0);
	if (!env_val)
		msh_perror_exit("init_msh",
			"set_home_env_var: env_val",
			strerror(errno), EXIT_FAILURE);
	msh_env_setvar(env_list, env_key, env_val);
	env_val = ft_strdup(env_val);
	if (!env_val)
		msh_perror_exit("init_msh",
			"set_home_env_var: env_val",
			"malloc fail.", EXIT_FAILURE);
	return (env_val);
}

void	msh_history_load(const char *filename);

static void	set_history_file_env_var(t_list **env_list, char *filename)
{
	char	*env_key;
	char	*env_val;

	env_key = NULL;
	env_key = ft_strdup("MSH_HIST_FILE");
	env_val = NULL;
	env_val = ft_strdup(filename);
	if (!env_key || !env_val)
		msh_perror_exit("init_msh",
			"set_history_file_env_var: env_key or env_val",
			"malloc fail.", EXIT_FAILURE);
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
	{
		tmp = ft_strdup(tmp);
		if (!tmp)
			return (msh_perror_exit("init_msh", "ft_strdup(tmp)",
					"malloc fail.", EXIT_FAILURE));
	}
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
