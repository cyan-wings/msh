#ifndef MSH_PARSE_H
# define MSH_PARSE_H

# include <stdlib.h>
# include <unistd.h>

# ifdef ARCH_X86_64
#  include "readline.h"
# else
#  include <readline.h>
# endif

# include "ft_char_utils.h"
# include "ft_mem_utils.h"
# include "ft_string_utils.h"
# include "ft_print_utils.h"

# include "msh_perror.h"
# include "msh_tokenise.h"

typedef struct s_ast
{
	char			*type;
	struct s_ast	**children;
	int				child_count;
	char			*value;
}	t_ast;

//PARSE
int		msh_parse(t_list *token_list, t_ast **root);

//AST_UTILS
t_ast	*msh_parse_astnew(char *type, char *value);
void	msh_parse_astadd_child(t_ast *parent, t_ast *child);
void	msh_parse_astprint(t_ast *node, int indent);
void	msh_parse_astfree(t_ast **root_node);

//PARSE_EXPRESSION
t_ast	*msh_parse_grouping(t_list **token_ptr);
t_ast	*msh_parse_list(t_list **token_ptr);
t_ast	*msh_parse_pipeline(t_list **token_ptr);
t_ast	*msh_parse_cmd(t_list **token_ptr);


#endif