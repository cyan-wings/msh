/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:04:11 by myeow             #+#    #+#             */
/*   Updated: 2024/05/31 13:20:40 by myeow            ###   ########.fr       */
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

typedef struct s_token
{
	char	*string;
}	t_token;

//DEBUG
void	minishell_print_token_list(t_list *token_list);

//MINISHELL_TOKENISE
void	minishell_tokenise(char *input, t_list **token_list);
void	minishell_tokenise_free(t_list **token_list);

//MINISHELL_ENV
void	minishell_env_init(t_list **env_list);
char	*minishell_env_getvar(t_list *env_list, char *k);
void	minishell_env_setvar(t_list **env_list, char *k, char *v);
void	minishell_env_free(t_list **env_list);

//MINISHELL_HISTORY
void	minishell_load_history(const char *filename);
void	minishell_save_history(char *input, const char *filename);

//ERROR_HANDLING
void	minishell_perror_exit(char *s, int status);

//MINISHELL
char	*minishell_prompt(t_list *env_list);

#endif
