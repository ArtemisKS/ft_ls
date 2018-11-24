/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:26:17 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 14:26:23 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destptr, const void *srcptr, size_t num)
{
	size_t		i;
	char		*tmp;
	const char	*tmp1;

	tmp = destptr;
	tmp1 = srcptr;
	i = 0;
	while (i < num)
	{
		tmp[i] = tmp1[i];
		i++;
	}
	destptr = tmp;
	return (destptr);
}
