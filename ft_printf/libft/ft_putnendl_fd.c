/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnendl_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:31:01 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/14 23:31:03 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_putnendl_fd(char const *s, int fd, size_t len)
{
	ssize_t		endlen;

	if (!s)
		return (0);
	endlen = write(fd, s, len);
	endlen += write(fd, "\n", 1);
	return (endlen);
}
