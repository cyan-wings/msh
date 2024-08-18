#include "msh.h"

char **get_var_arr(t_ast *node) {
	int i;
	char **res;

	if (ft_strcmp(node->type, "arguments"))
		return NULL;
	i = -1;
	res = (char **)malloc(sizeof(char *) * (node->child_count + 1));
	while (++i < node->child_count) {
		res[i] = ft_strdup(node->children[i]->value);
	}
	res[i] = NULL;
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
