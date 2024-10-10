#include "msh_execute.h"

static int	check_null_param(t_ast *node, char ***argv_arr,
				t_list *env_list)
{
	if (!node)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
                    "node is NULL.");
		return (0);
	}
	if (!argv_arr)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
                    "argv_arr is NULL.");
		return (0);
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
					"env_list is NULL.");
		return (0);
	}
	return (1);
}

static void	free_redir_st_arr(t_redir_st **redir_st_arr)
{
	int	i;

	i = -1;
	if (redir_st_arr)
	{
		while (redir_st_arr[++i])
			ft_memdel((void **) &redir_st_arr[i]);
		ft_memdel((void **) &redir_st_arr);
	}
}

int msh_execute_simple_cmd_builtin(t_ast *node, t_list **env_list, char **argv_arr, int subshell_flag)
{
    t_bif	*builtin_func;
    int     status;
    t_redir_st  **redir_st_arr;

    if (!check_null_param(node, argv_arr, env_list))
        return (ERROR);
    builtin_func = msh_builtins_get_builtin(argv_arr[0]);
    if (builtin_func)
    {
        status = msh_execute_simple_cmd_redirs(node->children[1], &redir_st_arr);
        if (status != ERROR)
            status = (*builtin_func)(node->children[0]->child_count, argv_arr, env_list, subshell_flag);
        msh_execute_simple_cmd_redirs_restore(&redir_st_arr);
        free_redir_st_arr(redir_st_arr);
        return (status);
    }
    return (ERROR);
}