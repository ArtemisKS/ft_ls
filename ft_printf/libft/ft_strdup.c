/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 21:04:40 by akupriia          #+#    #+#             */
/*   Updated: 2017/09/27 21:04:42 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*t;
	int		n;
	char	*copy;

	n = 0;
	while (src[n++] != '\0')
		;
	if (!(copy = (char*)malloc(n)))
		return (NULL);
	t = copy;
	while ((*t++ = *src++) != '\0')
		;
	return (copy);
}
