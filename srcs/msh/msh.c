/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:36:59 by myeow             #+#    #+#             */
/*   Updated: 2024/10/24 22:00:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <termios.h>
#include <errno.h>
#include <signal.h>
#include "ft_print_utils.h"
#include <unistd.h>
#include "readline.h"
#include <stdlib.h>
#include "ft_mem_utils.h"

void	msh_history_load(const char *filename);

void	msh_env_init(t_list **env_list);

static void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_signal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		msh_perror_exit("tcgetattr\n", errno);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		msh_perror_exit("tcsetattr\n", errno);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_DFL);
}

char	*msh_input_get(t_list *env_list);

void	msh_input_process(char *input, t_list **env_list,
			t_global *global);

//system("leaks msh -q");
int	main(void)
{
	t_global	global;
	t_list		*env_list;
	char		*input;

	global = (t_global){0};
	env_list = NULL;
	msh_history_load(HISTORY_FILE);
	msh_env_init(&env_list);
	input = NULL;
	while (1)
	{
		init_signal();
		input = msh_input_get(env_list);
		if (!input)
			exit(EXIT_SUCCESS);
		msh_input_process(input, &env_list, &global);
		ft_memdel((void **)&input);
	}
	msh_env_free(&env_list);
	return (0);
}
