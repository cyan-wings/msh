/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_wildcards.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:19:16 by myeow             #+#    #+#             */
/*   Updated: 2024/07/11 20:10:02 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "dirent.h"

void	msh_expansion_quotes(char **strptr);

static char	*find_close_quote(char *str, char quote_type)
{
	++str;
	while (*str)
	{
		if (*str == quote_type)
			return (++str);
		++str;
	}
	return (str);
}

static int	check_wildcards(char *str)
{
	while (str)
	{
		if (*str == '\"' || *str == '\'')
			find_close_quote(str, *str);
		if (*str == '*')
			return (1);
	}
	return (0);
}

static void	append_to_new_str_if_match(char *pattern, char **new_strptr,
		struct dirent *entry)
{
	static int	flag = 0;

	if (*(entry->d_name) != '.' && ft_strmatch_pattern(entry->d_name, pattern))
	{
		if (flag)
			ft_strappend(new_strptr, " ");
		else
			flag = 1;
		ft_strappend(new_strptr, entry->d_name);
	}
}

/*
 * May want to call msh_perror_exit instead
 */
void	get_matched_files(char *pattern, char **new_strptr)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		msh_perror_exit("opendir error", 1);
	entry = readdir(dir);
	while (entry)
	{
		append_to_new_str_if_match(pattern, new_strptr, entry);
		entry = readdir(dir);
	}
	if (closedir(dir) == -1)
		msh_perror_exit("closedir error", 1);
}

void	msh_expansion_wildcards(char **strptr)
{
	char	*pattern;
	char	*new_str;

	if (!check_wildcards(*strptr))
		return ;
	pattern = 0;
	pattern = ft_strdup(*strptr);
	if (!pattern)
		msh_perror_exit("No mem to malloc pattern", 1);
	msh_expansion_quotes(&pattern);
	new_str = 0;
	get_matched_files(pattern, &new_str);
	if (!new_str)
		return ;
	ft_memdel((void **) strptr);
	*strptr = new_str;
}
