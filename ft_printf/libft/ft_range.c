/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:30:14 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/14 23:30:15 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_range(int min, int max)
{
	int	i;
	int	*p;

	if (min >= max)
		return (0);
	p = (int *)malloc(sizeof(int) * (max - min));
	if (p == NULL)
		return (NULL);
	i = -1;
	while (min < max)
	{
		p[++i] = min;
		min++;
	}
	return (p);
}
