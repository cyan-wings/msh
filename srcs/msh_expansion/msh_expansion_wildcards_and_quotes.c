/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_wildcards_and_quotes.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:00:47 by myeow             #+#    #+#             */
/*   Updated: 2024/07/12 21:02:04 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "dirent.h"

void	msh_expansion_quotes(char **strptr);

static int	check_and_replace_wildcards(char **strptr)
{
	int	flag;
	int	quote_type;
	int	i;

	flag = 0;
	quote_type = 0;
	i = -1;
	while ((*strptr)[++i])
	{
		if ((*strptr)[i] == '*')
		{
			(*strptr)[i] = -1;
			flag = 1;
		}
		else if ((*strptr)[i] == '\"' || (*strptr)[i] == '\'')
		{
			quote_type = (*strptr)[i];
			while ((*strptr)[++i] != quote_type)
				;
		}
	}
	return (flag);
}

static void	append_to_new_str_if_match(char *pattern, char **new_strptr,
		struct dirent *entry, int *n)
{
	if (*(entry->d_name) != '.' && ft_strmatch_pattern(entry->d_name, pattern))
	{
		if (*n)
			ft_strappend(new_strptr, " ");
		ft_strappend(new_strptr, entry->d_name);
		++*n;
	}
}

/*
 * May want to call msh_perror_exit instead
 */
static int	get_matched_files(char *pattern, char **new_strptr)
{
	DIR				*dir;
	struct dirent	*entry;
	int				n;

	dir = opendir(".");
	if (!dir)
		msh_perror_exit("opendir error", 1);
	entry = readdir(dir);
	n = 0;
	while (entry)
	{
		append_to_new_str_if_match(pattern, new_strptr, entry, &n);
		entry = readdir(dir);
	}
	if (closedir(dir) == -1)
		msh_perror_exit("closedir error", 1);
	return (n);
}

static void	revert_wildcards_to_literal(char **strptr)
{
	int	i;

	i = -1;
	while ((*strptr)[++i])
	{
		if ((*strptr)[i] == -1)
			(*strptr)[i] = '*';
	}
	return ;
}

/*
 * This function takes a pointer to the string, and replaces the 
 * string in the pointer with a new processed string.
 *
 * @params
 * 		flag: 	Indicates whether there are any unquoted wildcards
 * 				which indicates a pattern to match filenames.
 * 		new_str:	The new string that replaces the string in strptr
 * 					if flag is 1. Which means there is a pattern to
 * 					match. When there is a pattern to match, the string
 * 					would be filenames that matches the pattern instead
 * 					of the string in the strptr.
 * 		n: 	0 means no match at all, which means the string in the
 * 			strptr must be treated literally.
 * 			The n value represents the number of filename matches to
 * 			the pattern.
 *
 * 	When flag is 0, no unquoted wildcards are found which safely assumes
 * 	no '*' character replacements took place. The string can be
 * 	safely treated as a literal. Thus, quote removals can be performed, 
 * 	skipping the whole wildcard process.
 *
 * 	When n is 0, no match was found. The string must be treated as a 
 * 	literal. The replaced '*' must be reverted to its original form.
 */
void	msh_expansion_wildcards_and_quotes(char **strptr)
{
	int		flag;
	char	*new_str;
	int		n;

	flag = -1;
	flag = check_and_replace_wildcards(strptr);
	msh_expansion_quotes(strptr);
	if (!flag)
		return ;
	new_str = 0;
	n = -1;
	n = get_matched_files(*strptr, &new_str);
	if (!n)
		revert_wildcards_to_literal(strptr);
	else
	{
		ft_memdel((void **) strptr);
		*strptr = new_str;
	}
}