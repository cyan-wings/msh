#include "ft_string_utils.h"
#include "msh.h"
#include <stdio.h>

//get ARGUMENTS FOR EXECVE
char **get_var_arr(t_ast *node) {
	int i;
	char **res;
	t_ast *current;

	current = node->children[1];
	if (ft_strcmp(current->type, "arguments"))
		return NULL;
	i = -1;
	res = (char **)malloc(sizeof(char *) * (current->child_count + 2));
	res[0] = ft_strdup(node->children[0]->value);
	while (++i < current->child_count) {
		res[i+1] = ft_strdup(current->children[i]->value);
	}
	res[i+1] = NULL;
	return res;
}

int check_is_plugin(char *executable) {
	//TODO: make it return according to the builtin list index
	if (!ft_strcmp(executable, "cd") 
		|| !ft_strcmp(executable, "export")
		|| !ft_strcmp(executable, "exit")
		|| !ft_strcmp(executable, "unset")
		|| !ft_strcmp(executable, "echo")
		|| !ft_strcmp(executable, "pwd")
		|| !ft_strcmp(executable, "env"))
		return 1;
	return 0;
}
