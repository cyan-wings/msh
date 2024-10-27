/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:06:21 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 15:53:31 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXECUTE_H
# define MSH_EXECUTE_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>

# include "ft_lst_utils.h"
# include "ft_mem_utils.h"
# include "ft_string_utils.h"

# include "msh_perror.h"
# include "msh_utils.h"
# include "msh_signal.h"
# include "msh_parse.h"
# include "msh_builtins.h"

typedef enum e_redirection_type
{
	REDIR_ERR = 0,
	REDIR_IN = 1,
	REDIR_OUT = 2,
	REDIR_HERE = 3,
	REDIR_APP = 4,
}	t_redir_type;

typedef struct s_redirections_state
{
	int	fd_new;
	int	fd_backup;
}	t_redir_st;

int		msh_execute(t_ast *node, t_list **env_list, int subshell_flag);
int		msh_execute_exit_status_get(void);
void	msh_execute_exit_status_set(int status);
void	msh_execute_free(char **argv_arr, char **envp_arr);
void	msh_execute_free_exit(int status, char **argv_arr, char **envp_arr);
int		msh_execute_simple_cmd_redirs(t_ast *redirs_node,
			t_redir_st ***redir_st_arr, t_list **env_list);
void	msh_execute_simple_cmd_redirs_restore(t_redir_st ***redir_st_arr);
int		msh_execute_simple_cmd_init(t_ast *node, t_list **env_list,
			char ***envp_arr, char ***argv_arr);
int		msh_execute_simple_cmd_builtin(t_ast *node, t_list **env_list,
			char **argv_arr, int subshell_flag);
int		msh_execute_simple_cmd_execute(char **argv_arr, char **envp_arr,
			t_list **env_list);
int		msh_execute_wait_pid(int prev_pid, char *name);

#endif
