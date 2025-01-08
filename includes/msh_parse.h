/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:07:15 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 14:18:13 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSE_H
# define MSH_PARSE_H

# include <stdlib.h>
# include <unistd.h>

# include "readline.h"

# include "ft_lst_utils.h"
# include "ft_char_utils.h"
# include "ft_mem_utils.h"
# include "ft_string_utils.h"
# include "ft_print_utils.h"

# include "msh_perror.h"
# include "msh_tokenise.h"
# include "msh_env.h"

# define PAD_R -2
# define DELIM_R -3
# define SPACE_R -32

# ifndef HEREDOC_SIGINT_ERROR
#  define HEREDOC_SIGINT_ERROR 7
# endif

# ifndef AMBIGUOUS_REDIR_ERROR
#  define AMBIGUOUS_REDIR_ERROR 11
# endif

typedef struct s_ast
{
	char			*type;
	struct s_ast	**children;
	int				child_count;
	char			*value;
}	t_ast;

//PARSE
int		msh_parse(t_list *token_list, t_ast **root, t_list *env_list);

//AST_UTILS
t_ast	*msh_parse_astnew(char *type, char *value);
void	msh_parse_astadd_child(t_ast *parent, t_ast *child);
void	msh_parse_astprint(t_ast *node, int indent, int null_flag);
void	msh_parse_astfree(t_ast **root_node);

//PARSE_EXPRESSION
int		msh_parse_list(t_list **token_ptr, t_ast **list_node, t_list *env_list);
int		msh_parse_pipeline(t_list **token_ptr, t_ast **pipeline_node,
			t_list *env_list);
int		msh_parse_grouping(t_list **token_ptr, t_ast **grouping_node,
			t_list *env_list);
int		msh_parse_cmd(t_list **token_ptr, t_ast **cmd_nod, t_list *env_list);

#endif
