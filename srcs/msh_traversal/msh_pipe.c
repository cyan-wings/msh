#include "ft_lst_utils.h"
#include "msh.h"
#include <stdio.h>

void	handle_redirection_out(int *fd, t_ast *node);
void	handle_redirection_in(int *fd, t_ast *node);
void handle_redirection(t_ast *node);
void	run_execve(t_ast *node, t_list *env);
void	child_node(t_ast *node, t_list *env );
void	run_execve(t_ast *node, t_list *env);
int	multi_cmd(t_ast *node, pid_t *pid, t_list **env_list, t_bif *builtin_list);
int	single_cmd(t_ast *node, pid_t *pid, t_list **env_list, t_bif *builtin_list);
void	child_handle_pipes(int pipe_fd[2][2], int current, int total);
void	parent_handle_pipes(int pipe_fd[2][2], int current, int total);

int	single_cmd(t_ast *node, pid_t *pid, t_list **env_list, t_bif *builtin_list)
{
	int	res;
	t_ast *current;

	current = node->children[0];
	if (current[0]->value == plugin)
		return -1;
	// TODO: run builtin
		// res = builtin_list[builtin](current[1]->value);
	else
	{
		pid[0] = fork();
		if (pid[0] == 0)
			child_node(current, NULL);
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
			child_node(node->children[i], env);
			break;
		}
		else
			parent_handle_pipes(pipe_fd, i, node->child_count);
	}
	return -1;
}

void	parent_handle_pipes(int pipe_fd[2][2], int current, int total)
{
	if (current != 0)
		close(pipe_fd[1][0]);
	if (current + 1 != total)
		pipe_fd[1][0] = pipe_fd[0][0];
	close(pipe_fd[0][1]);
	if (current + 1 == total)
		close(pipe_fd[0][0]);

	// if (current->prev) {
	// 	close(pipe_fd[1][0]);
	// }
	// if (current->next) {
	// 	pipe_fd[1][0] = pipe_fd[0][0];
	// }
	// close(pipe_fd[0][1]);
	// if (!current->next) 
	// 	close(pipe_fd[0][0]);
}

void	child_handle_pipes(int pipe_fd[2][2], int current, int total)
{
	if (current != 0)
		ft_dup2(pipe_fd[0][1], STDOUT_FILENO);
	if (current + 1 != total)
		ft_dup2(pipe_fd[1][0], STDIN_FILENO);
	close(pipe_fd[0][0]);
	if (current + 1 == total)
		close(pipe_fd[1][0]);
	close(pipe_fd[0][1]);

	// if (current->next)
	// 	ft_dup2(current->raw, pipe_fd[0][1], STDOUT_FILENO);
	// if (current->prev)
	// 	ft_dup2(current->raw, pipe_fd[1][0], STDIN_FILENO);
	// close(pipe_fd[0][0]);
	// if (current->prev)
	// 	close(pipe_fd[1][0]);
	// close(pipe_fd[0][1]);
}

void ft_dup2(int oldfd, int newfd) {
  int res;

  res = dup2(oldfd, newfd);
  if (res == -1) {
    // write(2, str, ft_strlen(str));
    // write(2, ": ", 2);
    write(2, "dup2 failed", 11);
    exit(1);
  }
}

void	child_node(t_ast *node, t_list **env list)
{
	if (node->child_count == 2)
		handle_redirection(node->children[1]);
	if (node->children[0]->type != NONE)
		exit(builtin());
	else
		run_execve(node->children[1], env);
}

void	run_execve(t_ast *node, t_list **env)
{
	int	i;
	char **path;
	int res;

	i = -1;
	path = ft_split(msh_env_getvar(*env, "PATH"), ':');
	while (path[++i])
	{
		filepath = ft_strjoin(path[i], node->children[0]);
		res = execve(filepath, node->children[1], env);
		free(filepath);
		if (res != -1)
			break;
	}
	if (!path[i])
	{
		perror("Command not found");
		exit(127);
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

void handle_redirection(t_ast *node)
{
	int	i;
	int in;
	int out;
	t_ast *current;

	i = -1;
	in = -69;
	out = -69;
	while (++i < node->child_count)
	{
		current = node->children[i]
		if (!ft_strcmp(node->value, "<<") || ft_strcmp(node->value, "<"))	
			handle_redirection_in(&in, node);
		else (!ft_strcmp(node->value, ">") || ft_strcmp(node->value, ">>"))	
			handle_redirection_out(&out, node);
	}
	if (in != -69)
		ft_dup2(in, STDIN_FILENO);
	if (out != -69)
		ft_dup2(out, STDOUT_FILENO);
}

void	handle_redirection_in(int *fd, t_ast *node)
{
	if (*fd != 69)
	{
		close(*fd);
		*fd = -69;
	}
	if (!ft_strcmp( node->value, "<" ))
		fd = open(node->children[0], O_RDONLY);
	else
		fd = open("here_doc", O_RDONLY);
}

void	handle_redirection_out(int *fd, t_ast *node)
{
	if (*fd != 69)
	{
		close(*in);
		*fd = -69;
	}
	if (!ft_strcmp( node->value, ">>" ))
		fd = open(node->children[0],O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH); 
	else
		fd = open(node->children[0]), O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
}
