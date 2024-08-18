#include "msh.h"

void handle_pipeline(t_ast *node, t_list **env_list)
{
	int	i;
	pid_t *pid_list;
	int	status;

	pid_list = ft_calloc(node->child_count, sizeof(pid_t));
	if (node->child_count == 1)
		single_cmd(node, pid_list, env_list);
	else
		multi_cmd(node, pid_list, env_list);
	i = -1;
	while (++i <= node->child_count) {
		if (waitpid(pid_list[i], &status, 0) == -1)
		  perror("waitpid failed");
		if (WIFEXITED(status))
			printf("%i\n",  WIFEXITED(status));
		  // ms->latest_err = WEXITSTATUS(status);
	  }
	free(pid_list);
}

void	handle_list_op(t_ast *node)
{
	return ;
}

void	handle_node(t_ast *node)
{
	if (ft_strcmp(node->type, "pipeline"))
		handle_pipeline(node);
	else if (ft_strcmp(node->type, "list_op"))
		return;
	else if (ft_strcmp(node->type, "grouping"))
		return;
	else
		return;
		// handle_pipeline(node);
}

void	traversal(t_ast *node, t_list **env_list, t_bif *builtin_list)
{
	int	i;

	if (node == NULL)
		return ;

	// if (ft_strcmp(node->type, "pipeline")==0)
	// 	return ;
	// handle_node(node);

	i = -1;
	// printf("%s: %s\n", node->type, node->value);
	while (++i < node->child_count)
		traversal(node->children[i], env_list, builtin_list);


	printf("%s: %s\n", node->type, node->value);
}
