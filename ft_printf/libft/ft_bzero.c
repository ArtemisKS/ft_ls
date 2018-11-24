/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 21:00:16 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/14 20:44:48 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t				*size_t_s;
	unsigned char		*uchar_s;
	size_t				i;

	size_t_s = (size_t *)s;
	uchar_s = (unsigned char *)s;
	i = n - (n % sizeof(size_t));
	while (i < n)
		uchar_s[i++] = 0;
	n /= sizeof(size_t);
	while (n)
		size_t_s[--n] = 0;
}
