/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:38:03 by akupriia          #+#    #+#             */
/*   Updated: 2017/10/27 21:38:04 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	find_word(size_t *i, size_t *j, char const *s, char c)
{
	*i = *j;
	while (s[(*i)] == c && s[(*i)])
		*i = *i + 1;
	*j = *i;
	while (s[(*j)] != c && s[(*j)])
		*j = *j + 1;
}

static	char	**freedom(char **buf, size_t y, char ***buff)
{
	while (y)
		free(buf[--y]);
	free(buf);
	*buff = NULL;
	return (NULL);
}

static	char	**appropriation(char **buf, size_t wn, char const *s, char c)
{
	size_t	x;
	size_t	y;
	size_t	i;
	size_t	j;

	y = 0;
	j = 0;
	while (y < wn)
	{
		x = 0;
		find_word(&i, &j, s, c);
		buf[y] = (char *)malloc(sizeof(char) * (j - i + 1));
		if (buf[y] == NULL)
			return (freedom(buf, y, &buf));
		while (i < j)
			buf[y][x++] = s[i++];
		buf[y++][x] = '\0';
	}
	buf[y] = NULL;
	return (buf);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**buf;
	size_t	wn;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	wn = 0;
	if (s[0] != c && s[0])
		wn++;
	while (s[i++])
		if (s[i - 1] == c && s[i] != c && s[i])
			wn++;
	buf = (char **)malloc(sizeof(char *) * (wn + 1));
	if (buf == NULL)
		return (NULL);
	return (appropriation(buf, wn, s, c));
}
