/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:15:50 by akupriia          #+#    #+#             */
/*   Updated: 2018/05/17 15:15:51 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr_start(const char *str, const char *to_find)
{
	int i;

	i = 0;
	if (!to_find[i])
		return ((char*)str);
	while (*(str + i) == *(to_find + i))
		if (*(to_find + i + 1) == '\0')
			return ((char*)str);
		else if (*(str + i++) == '\0')
			return (0);
	return (0);
}
