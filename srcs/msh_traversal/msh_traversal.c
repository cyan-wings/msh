#include "ft_mem_utils.h"
#include "ft_string_utils.h"
#include "msh.h"
#include <stdio.h>
#include <sys/wait.h>

void handle_pipeline(t_ast *node, t_list **env_list, t_bif *builtin_list)
{
	int	i;
	pid_t *pid_list;
	int	status;

	pid_list = ft_calloc(node->child_count, sizeof(pid_t));
	// printf("\ntype: %s\n child_count: %i\n node value: %s\n", node->type, node->child_count, node->value);
	if (node->child_count <= 1)
		single_cmd(node, pid_list, env_list, builtin_list);
	else
		multi_cmd(node, pid_list, env_list, builtin_list);
	i = -1;
	while (++i < node->child_count) {
		if (waitpid(pid_list[i], &status, 0) == -1)
		  perror("waitpid failed");
		if (WIFEXITED(status)) {
			// printf("exit status is %d\n",  WEXITSTATUS(status));
			g_exit_status = WEXITSTATUS(status);
			return;
		}
		  // ms->latest_err = WEXITSTATUS(status);
	  }
	free(pid_list);
}

int	handle_list_op(t_ast *node)
{
	if (ft_strcmp(node->type, "list_op"))
		return 0;
	if (!ft_strcmp( node->value, "&&") && g_exit_status != 0)
		return 1;
	if (!ft_strcmp( node->value, "||") && g_exit_status == 0)
		return 1;
	return 0;
//TODO: what to do when its valid and when its not
}

void	handle_grouping(t_ast *node, t_list **env_list, t_bif *builtin_list)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) {
		traversal(node->children[0], env_list, builtin_list);
	} else {
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid failed in subshell");
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
			// printf("%i\n", WIFEXITED(status));
	}
}

int	handle_node(t_ast *node, t_list **env_list, t_bif *builtin_list)
{
	int res;

	res = 0;
	if (!ft_strcmp(node->type, "pipeline"))
		handle_pipeline(node, env_list, builtin_list);
	else if (!ft_strcmp(node->type, "list_op"))
		res = handle_list_op(node);
	else if (!ft_strcmp(node->type, "grouping"))
		handle_grouping(node, env_list, builtin_list);
	else
		return res;
		// handle_pipeline(node);
	return res;
}

int	traversal(t_ast *node, t_list **env_list, t_bif *builtin_list)
{
	int	i;
	// int should_break;

	if (node == NULL)
		return 0;

	// should_break = 0;

	i = -1;
	// printf("%s: %s\n", node->type, node->value);
	while (++i < node->child_count) {
		if (traversal(node->children[i], env_list, builtin_list))
			return 1;
	}


	if (handle_node(node, env_list, builtin_list))
		return 1;
	return 0;
	// printf("%s: %s\n\n", node->type, node->value);
}
