/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_root.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:30:08 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/14 23:30:09 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_root(int n, int rt)
{
	int					i;
	unsigned long int	j;

	if (n == 1 && rt > 1)
		return (1);
	if (n <= 3 || rt <= 1)
		return (0);
	i = 1;
	while (++i)
	{
		j = ft_pow(i, rt);
		if (j > (unsigned long int)n)
			return (-1);
		if (j == (unsigned long int)n)
			return (i);
	}
	return (0);
}
