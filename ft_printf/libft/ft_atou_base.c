/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:38:41 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/14 23:38:42 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_atou_base function inputs (char *)s - array of chars, which only include
**	numbers and '-' sign, numbers may be at any base from 2nd to 36th, and
**	outputs decimal unsigned longinteger value, which represent input number.
**
**	i[0] -- len of (char *)s iterator(i);
**	i[1] -- len of (char *)s buffer(i_buf);
**	i[2] -- "0123456789ABCDEF" iterator(j);
**	i[3] -- buf[0] == '-' ? -1 : 1;
*/

unsigned long		ft_atou_base(const char *s, int base)
{
	int				i[4];
	unsigned long	res;
	char			*buf;
	const	char	st[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	buf = ft_strtrim(s);
	i[3] = buf[0] == '-' ? -1 : 1;
	buf = (buf[0] == '-' || buf[0] == '+') ? (buf + 1) : buf;
	i[1] = -1;
	while (buf[++i[1]])
		buf[i[1]] = ft_toupper(buf[i[1]]);
	i[0] = i[1]--;
	res = 0;
	while (--(i[0]) + 1)
	{
		i[2] = 0;
		while ((st[i[2]] != buf[i[0]]) && i[2] < base)
			i[2]++;
		res += i[2] * (!(i[1] - i[0]) ? 1 : (ft_pow(base, i[1] - i[0])));
	}
	free(buf);
	return ((res * i[3]));
}
