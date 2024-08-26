/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:31:55 by myeow             #+#    #+#             */
/*   Updated: 2024/07/11 16:29:50 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

#include "ft_lst_utils.h"
# define HISTORY_FILE ".msh_history"

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "get_next_line.h"

extern int g_exit_status;

/*
# define OA "<"
# define CA ">"
# define DOA "<<"
# define DCA ">>"
# define PIPE "|"
# define OP "("
# define CP ")"
# define AND "&&"
# define OR "||"
*/
struct s_ast;
typedef int (*t_bif)(struct s_ast *node, t_list **env_list);
typedef struct s_env
{
	char		*key;
	char		*val;
}	t_env;

typedef enum e_operator_type
{
	DEFAULT,
	REDIRECT,
	CONTROL,
}	t_operator_type;

typedef enum e_token_type
{
	WORD = 5,
	OPERATOR = 7,
	REDIR_OP = 8,
	CTRL_OP = 9
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

/*
 * Consider changing the type to an enum
 */
typedef struct s_ast
{
	char			*type;
	struct s_ast	**children;
	int				child_count;
	char			*value;
}	t_ast;

//MSH_EXPANSION
void	msh_expansion(t_ast *node, t_list *env_list);

//msh_PARSE_EXPRESSION
t_ast	*msh_parse_grouping(t_list **token_ptr);
t_ast	*msh_parse_list(t_list **token_ptr);
t_ast	*msh_parse_pipeline(t_list **token_ptr);
t_ast	*msh_parse_cmd(t_list **token_ptr);

//msh_PARSE_AST
t_ast	*msh_parse_astnew(char *type, char *value);
void	msh_parse_astadd_child(t_ast *parent, t_ast *child);
void	msh_parse_astprint(t_ast *node, int indent);
void	msh_parse_astfree(t_ast **root_node);

//msh_PARSE_TOKEN
int		msh_parse_token(t_list *token_list);
int		msh_parse(t_list *token_list, t_ast **root);

//DEBUG
void	msh_print_token_list(t_list *token_list);

//msh_TOKENISE
int		msh_tokenise(char *input, t_list **token_list);
void	msh_tokenise_free(t_list **token_list);
void	msh_tokenise_get_next_token(t_list **token_ptr);

//msh_TRAVERSAL
int	traversal(t_ast *node, t_list **env_list, t_bif *builtin_list);

//msh_ENV
void	msh_env_init(t_list **env_list);
char	*msh_env_getvar(t_list *env_list, char *k);
void	msh_env_setvar(t_list **env_list, char *k, char *v);
void	msh_env_free(t_list **env_list);
char	**msh_env_get_array(t_list *env_list);

// msh_BUILTIN
void	msh_builtin_init(t_bif **builtin_list);

//utils
char **get_var_arr(t_ast *node) ;
int check_is_plugin(char *executable) ;

// msh_execution_UTILS
void	handle_redirection_in(int *fd, t_ast *node);
void	handle_redirection_out(int *fd, t_ast *node);
void	ft_dup2(int oldfd, int newfd) ;
void	handle_redirection(t_ast *node);
void	run_execve(t_ast *node, t_list **env_list);

// msh_execute
int		single_cmd(t_ast *node, pid_t *pid, t_list **env_list, t_bif *builtin_list);
int		multi_cmd(t_ast *node, pid_t *pid, t_list **env_list, t_bif *builtin_list);

// msh_signals
void	signal_init(void);
void 	sigint_handler(int sig);
void 	reset_signal(void);

//msh_HISTORY
void	msh_load_history(const char *filename);
void	msh_save_history(char *input, const char *filename);

//ERROR_HANDLING
void	msh_perror(char *error_msg);
void	msh_perror_exit(char *s, int status);

//msh
char	*msh_prompt(t_list *env_list);

#endif
