/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_expansion_wildcards.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:00:47 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 03:34:23 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "dirent.h"

/*
 * The * character is replaced with a -1 character value because it is
 * possible for a filename to include the * character.
 * The -1 will then be used later for pattern matching for 0-any chars.
 */
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
		if ((*strptr)[i] == '\"' || (*strptr)[i] == '\'')
		{
			quote_type = (*strptr)[i];
			while ((*strptr)[++i] != quote_type)
				;
		}
		if ((*strptr)[i] == '*')
		{
			(*strptr)[i] = -1;
			flag = 1;
		}
	}
	return (flag);
}

static void	append_to_new_str_if_match(char *pattern, char **new_strptr,
		struct dirent *entry, int *n)
{
	const char	chars[2] = {PAD_R, DELIM_R};
	static char	tmp[2] = {0, 0};

	if (*(entry->d_name) != '.' && ft_strmatch_pattern(entry->d_name, pattern))
	{
		tmp[0] = chars[1];
		if (*n)
			ft_strappend(new_strptr, (char *)tmp);
		tmp[0] = chars[0];
		ft_strvappend(new_strptr, (char *)tmp, entry->d_name, (char *)tmp,
			NULL);
		if (!*new_strptr)
			return (msh_perror_exit("msh_parse_expansion_wildcards",
					"append_to_new_str_if_match", "malloc fail.",
					EXIT_FAILURE));
		++*n;
	}
}

void	ft_strrpad(char **strptr, char padding);

/*
 * May want to call msh_perror_exit instead
 */
static int	get_matched_files(char *pattern, char **new_strptr)
{
	char			*pattern_ex;
	DIR				*dir;
	struct dirent	*entry;
	int				n;

	pattern_ex = NULL;
	pattern_ex = ft_strdup(pattern);
	if (!pattern_ex)
		msh_perror_exit("msh_parse_expansion_wildcards",
			"get_matched_files: opendir", "malloc fail.", EXIT_FAILURE);
	msh_parse_expansion_quotes(&pattern_ex);
	ft_strrpad(&pattern_ex, PAD_R);
	dir = opendir(".");
	if (!dir)
		msh_perror_exit("msh_parse_expansion_wildcards",
			"get_matched_files: opendir", strerror(errno), EXIT_FAILURE);
	entry = readdir(dir);
	n = 0;
	while (entry)
	{
		append_to_new_str_if_match(pattern_ex, new_strptr, entry, &n);
		entry = readdir(dir);
	}
	ft_memdel((void **)&pattern_ex);
	if (closedir(dir) == -1)
		msh_perror_exit("msh_parse_expansion_wildcards",
			"get_matched_files: closedir", strerror(errno), EXIT_FAILURE);
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
void	msh_parse_expansion_wildcards(char **strptr)
{
	int		flag;
	char	*new_str;
	int		n;

	if (!strptr)
		msh_perror("debug", "msh_parse_expansion_wildcards",
			"strptr is NULL.");
	if (!*strptr)
		return ;
	flag = -1;
	flag = check_and_replace_wildcards(strptr);
	if (!flag)
		return ;
	new_str = NULL;
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
