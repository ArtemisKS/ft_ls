/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:50:56 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/15 18:54:52 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** static void	ft_swap_arr(char *st1, char *st2, char *t1)
** {
** 	int i;
**
** 	i = 0;
** 	while (st1[i])
** 	{
** 		t1[i] = st1[i];
** 		i++;
** 	}
** 	i = 0;
** 	while (st2[i])
** 	{
** 		st1[i] = st2[i];
** 		i++;
** 	}
** 	st1[i] = '\0';
** 	i = 0;
** 	while (t1[i])
** 	{
** 		st2[i] = t1[i];
** 		i++;
** 	}
** 	st2[i] = '\0';
** }
**
** void		ft_swap(void *s1, void *s2)
** {
** 	char *t1;
** 	char *st1;
** 	char *st2;
**
** 	if (s1 && s2)
** 	{
** 		st1 = (char*)s1;
** 		st2 = (char*)s2;
** 		t1 = (char*)malloc(sizeof(char) * ft_strlen(st1));
** 		ft_swap_arr(st1, st2, t1);
** 	}
** }
*/

void		ft_swap(void **s1, void **s2)
{
	void	*t;

	if (*s1 && *s2)
	{
		t = *s1;
		*s1 = *s2;
		*s2 = t;
	}
}
