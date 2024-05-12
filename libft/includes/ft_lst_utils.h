/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:38:22 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:50:36 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_UTILS_H
# define FT_LST_UTILS_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del) (void *));
void	ft_lstclear(t_list **lst, void (*del) (void *));
void	ft_lstiter(t_list *lst, void (*f) (void *));
t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del) (void *));
void	ft_lstprint(t_list *lst, char sep);
int		ft_lstmin(t_list *lst);
int		ft_lstmax(t_list *lst);
void	ft_lstrotate(t_list **lst);
void	ft_lstrevrotate(t_list **lst);
void	ft_lstswap(t_list **lst);
void	ft_lstpush(t_list **lst_a, t_list **lst_b);
int		ft_lstfind_index(t_list *lst, int n);

#endif
