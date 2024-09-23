/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:50:19 by myeow             #+#    #+#             */
/*   Updated: 2024/09/23 01:27:46 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_UTILS_H
# define FT_STRING_UTILS_H

# include <stddef.h>

int		ft_atoi(const char *str);
long	ft_atol(const char *str);
void	ft_free_ft_split(char **str_array);
char	*ft_itoa(int n);
char	*ft_itol(long n);
char	**ft_split(char const *s, char c);
char	**ft_split_tok(char *s, char const *set);
void	ft_strappend(char **ptr, char const *add);
char	*ft_strchr(const char *s, int c);
void	ft_strclr(char *s);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_strdel(char **as);
char	*ft_strdup(const char *s1);
char	*ft_strendptr(char *str);
void	ft_striteri(char *s, void (*f) (unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));
int		ft_strmatch_pattern(char *str, char *pattern);
void	ft_strnappend(size_t n, char **strptr, ...);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnew(size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtok(char *str, const char *sep);
char	*ft_strtok_r(char *str, const char *sep, char **last);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_strvappend(char **strptr, ...);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
