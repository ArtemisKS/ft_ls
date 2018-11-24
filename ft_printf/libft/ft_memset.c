/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:58:12 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/24 12:58:14 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t num)
{
	size_t	i;
	char	*tmp;

	tmp = (char*)memptr;
	i = 0;
	while (i < num)
	{
		tmp[i] = val;
		i++;
	}
	memptr = tmp;
	return (memptr);
}
