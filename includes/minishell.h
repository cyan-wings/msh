/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:04:11 by myeow             #+#    #+#             */
/*   Updated: 2024/06/30 19:41:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define HISTORY_FILE ".minishell_history"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
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
	WORD,
	OPERATOR,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;


typedef struct s_ast
{
	char			*type;
	struct s_ast	**children;
	int				child_count;
	char			*value;
}	t_ast;

//MINISHELL_PARSE_CMD
t_ast	*minishell_parse_cmd(t_list **token_ptr);
t_ast	*minishell_parse_cmd_arguments(t_list **token_ptr);

//MINISHELL_PARSE_AST
t_ast	*minishell_parse_astnew(char *type, char *value);
void	minishell_parse_astadd_child(t_ast *parent, t_ast *child);
void	minishell_parse_astprint(t_ast *node, int indent);
void	minishell_parse_astfree(t_ast *node);

//MINISHELL_PARSE_TOKEN
int		minishell_parse_token(t_list *token_list);
void	minishell_parse(t_list *token_list);

//DEBUG
void	minishell_print_token_list(t_list *token_list);

//MINISHELL_TOKENISE
void	minishell_tokenise(char *input, t_list **token_list);
void	minishell_tokenise_free(t_list **token_list);
void	minishell_tokenise_get_next_token(t_list **token_ptr);

//MINISHELL_ENV
void	minishell_env_init(t_list **env_list);
char	*minishell_env_getvar(t_list *env_list, char *k);
void	minishell_env_setvar(t_list **env_list, char *k, char *v);
void	minishell_env_free(t_list **env_list);

//MINISHELL_HISTORY
void	minishell_load_history(const char *filename);
void	minishell_save_history(char *input, const char *filename);

//ERROR_HANDLING
void	minishell_perror_exit(char *s, int status);

//MINISHELL
char	*minishell_prompt(t_list *env_list);

#endif
