#include "msh.h"

void	handle_redirection_in(int *fd, t_ast *node)
{
	if (*fd != 69)
	{
		close(*fd);
		*fd = -69;
	}
	if (!ft_strcmp( node->value, "<" ))
		*fd = open(node->children[0]->value, O_RDONLY);
	else
		*fd = open("here_doc", O_RDONLY);
}

void	handle_redirection_out(int *fd, t_ast *node)
{
	if (*fd != 69)
	{
		close(*fd);
		*fd = -69;
	}
	if (!ft_strcmp( node->value, ">>" ))
		*fd = open(node->children[0]->value, O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH); 
	else
		*fd = open(node->children[0]->value, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
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

void handle_redirection(t_ast *node)
{
	int	i;
	int in;
	int out;
	// t_ast *current;

	i = -1;
	in = -69;
	out = -69;
	while (++i < node->child_count)
	{
		current = node->children[i];
		if (!ft_strcmp(node->value, "<<") || !ft_strcmp(node->value, "<"))	
			handle_redirection_in(&in, node);
		else if (!ft_strcmp(node->value, ">") || !ft_strcmp(node->value, ">>"))	
			handle_redirection_out(&out, node);
	}
	if (in != -69)
		ft_dup2(in, STDIN_FILENO);
	if (out != -69)
		ft_dup2(out, STDOUT_FILENO);
}

void	run_execve(t_ast *node, t_list **env_list)
{
	int	i;
	char **path;
	char *filepath;
	int res;
	char **argv_arr;
	char **envp_arr;

	i = -1;
	path = ft_split(msh_env_getvar(*env_list, "PATH"), ':');
	argv_arr = get_var_arr(node->children[1]);
	envp_arr = msh_env_get_array(*env_list);
	while (path[++i])
	{
		filepath = ft_strjoin(path[i], node->children[0]->value);
		res = execve(filepath, argv_arr, envp_arr);
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
