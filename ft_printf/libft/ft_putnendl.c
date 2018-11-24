/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnendl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:30:57 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/14 23:30:58 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_putnendl(char const *s, size_t len)
{
	ssize_t		endlen;

	if (!s)
		return (0);
	endlen = write(1, s, len);
	endlen += write(1, "\n", 1);
	return (endlen);
}
