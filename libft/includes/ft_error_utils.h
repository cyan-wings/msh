/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:49:21 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:52:56 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_UTILS_H
# define FT_ERROR_UTILS_H

typedef enum s_error
{
	OK = 0,
	MALLOC_ERROR = -1337,
	NULL_ERROR = -10,
	SEG_FAULT = -42,
	UNDEFINED = -50,
	PARSE_ERROR = -48,
	SIZE_ERROR = -88,
	FORMAT_ERROR = -100,
}	t_error;

int	ft_error(t_error err_no);

#endif
