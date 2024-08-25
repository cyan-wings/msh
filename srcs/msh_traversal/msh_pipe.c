#include "msh.h"
#include <stdio.h>

static void	parent_handle_pipes(int pipe_fd[2][2], int current, int total)
{
	if (current != 0)
		close(pipe_fd[1][0]);
	if (current + 1 != total)
		pipe_fd[1][0] = pipe_fd[0][0];
	close(pipe_fd[0][1]);
	if (current + 1 == total)
		close(pipe_fd[0][0]);
}

static void	child_handle_pipes(int pipe_fd[2][2], int current, int total)
{
	if (current != total - 1)
		ft_dup2(pipe_fd[0][1], STDOUT_FILENO);
	if (current != 0)
		ft_dup2(pipe_fd[1][0], STDIN_FILENO);
	close(pipe_fd[0][0]);
	if (current != 0)
		close(pipe_fd[1][0]);
	close(pipe_fd[0][1]);
}



static void	child_node(t_ast *node, t_list **env_list, t_bif *builtin_list)
{
	if (node->children[2]->child_count > 0)
		handle_redirection(node->children[2]);
	if (check_is_plugin(node->children[0]->value))
		exit(builtin_list[0](node, env_list));
	else
		run_execve(node, env_list);
}

int	single_cmd(t_ast *node, pid_t *pid, t_list **env_list, t_bif *builtin_list)
{
	int	res;
	t_ast *current;

	current = node->children[0];
	if (check_is_plugin(current->children[0]->value)) {
		// TODO: run builtin
		// TODO: return builtin value
		// res = builtin_list[builtin](current[1]->value);
		printf("running builtin\n");
		(void) builtin_list;
		return 1;
	}
	else
	{
		pid[0] = fork();
		if (pid[0] == 0)
			child_node(current, env_list, builtin_list);
		res = -1;
	}
	return res;
}

int	multi_cmd(t_ast *node, pid_t *pid, t_list **env_list, t_bif *builtin_list)
{
	int pipe_fd[2][2];
	int	i;
	int	status;

	i = -1;
	status = 0;
	(void)status;
	while (++i < node->child_count)
	{
		if (pipe(pipe_fd[0]) == -1)
		{
			perror("pipe failed\n");
			exit(1);
		}
		pid[i] = fork();
		if (pid[i] == 0)
		{
			child_handle_pipes(pipe_fd, i, node->child_count);
			child_node(node->children[i], env_list, builtin_list);
			break;
		}
		else
			parent_handle_pipes(pipe_fd, i, node->child_count);
	}
	return -1;
}
