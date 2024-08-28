/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:31:55 by myeow             #+#    #+#             */
/*   Updated: 2024/08/28 20:36:06 by myeow            ###   ########.fr       */
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
# include "readline.h"
# include "history.h"
# include "libft.h"
# include "get_next_line.h"

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

typedef struct s_global
{
	char	status;
}			t_global;

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

typedef int (*t_bif)(t_ast *node, t_list **env_list);

// msh_BUILTIN
void	msh_builtin_init(t_bif **builtin_list);
int		msh_builtins_check_available(char *executable);

// msh_signals
void	signal_init(void);
void 	sigint_handler(int sig);
void 	msh_signal_reset(void);

//EXECUTE
int		msh_execute(t_ast *node, t_list **env_list, t_bif *builtin_list,
		t_global *global);

//MSH_EXPANSION
void	msh_expansion(t_ast *node, t_list *env_list);

//PARSE_EXPRESSION
t_ast	*msh_parse_grouping(t_list **token_ptr);
t_ast	*msh_parse_list(t_list **token_ptr);
t_ast	*msh_parse_pipeline(t_list **token_ptr);
t_ast	*msh_parse_cmd(t_list **token_ptr);

//AST_UTILS
t_ast	*msh_parse_astnew(char *type, char *value);
void	msh_parse_astadd_child(t_ast *parent, t_ast *child);
void	msh_parse_astprint(t_ast *node, int indent);
void	msh_parse_astfree(t_ast **root_node);

//PARSE_TOKEN
int		msh_parse_token(t_list *token_list);
int		msh_parse(t_list *token_list, t_ast **root);

//DEBUG
void	msh_print_token_list(t_list *token_list);

//TOKENISE
int		msh_tokenise(char *input, t_list **token_list);
void	msh_tokenise_free(t_list **token_list);
void	msh_tokenise_get_next_token(t_list **token_ptr);

//ENV
void	msh_env_init(t_list **env_list);
char	*msh_env_getvar(t_list *env_list, char *k);
void	msh_env_setvar(t_list **env_list, char *k, char *v);
void	msh_env_free(t_list **env_list);
char	**msh_env_get_array(t_list *env_list);

//HISTORY
void	msh_load_history(const char *filename);
void	msh_save_history(char *input, const char *filename);

//ERROR_HANDLING
void	msh_perror(char *error_msg);
void	msh_perror_exit(char *error_msg, int status);

//MSH
char	*msh_prompt(t_list *env_list);

#endif
