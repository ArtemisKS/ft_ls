/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:17:29 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 15:17:31 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*charr;
	unsigned char	c2;
	size_t			i;

	i = 0;
	charr = (unsigned char*)arr;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (charr[i] == c2)
			return (charr + i);
		i++;
	}
	return (NULL);
}
