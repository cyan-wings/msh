/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:04:11 by myeow             #+#    #+#             */
/*   Updated: 2024/05/27 22:33:09 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define HISTORY_FILE ".minishell_history"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_env
{
	char		*key;
	char		*val;
}	t_env;

//ENV
void	minishell_env_init(t_list **env_list);
void	minishell_env_setvar(t_list **env_list, char *k, char *v);
void	minishell_env_free(t_list **env_list);

void	minishell_load_history(const char *filename);
void	minishell_save_history(char *input, const char *filename);
void	minishell_perror_exit(char *s, int status);
char	*minishell_prompt(void);

#endif
