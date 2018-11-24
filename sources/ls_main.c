/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:52:35 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/15 20:21:04 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

#define FLAG_S	13

static inline bool		assign_flags(char opt)
{
	const char			chars[FLAG_S] = "GRaeiprstu@l1";
	const char			j[2] = {opt, 0};
	const size_t		index = ft_strstr(chars, j) - chars;
	int					res;

	res = 0;
	if (index < 12)
		((char *)(&g_fl->flags))[index] = true;
	else if (index == 12)
		((char *)(&g_fl->flags))[index - 1] = 2;
	else if ((opt == 'g') && (g_fl->flags.g = 1))
		g_fl->flags.mode = 1;
	else if ((opt == 'f') && (g_fl->flags.f = 1))
		g_fl->flags.a = 1;
	else if (opt == 'd' && (g_fl->flags.d = 1))
		g_fl->flags.cap_r = 0;
	else if ((opt == 'A') && (!g_fl->flags.a) && (g_fl->flags.cap_a = 1))
		g_fl->flags.a = 1;
	else if (opt != 'A')
		res = ft_dprintf(2, "%s%c\n%s", "./ft_ls: illegal option -- ", opt,
		"usage: ./ft_ls [-AGRadefgilprstu1@] [file ...]\n");
	return (res != 0);
}

static inline int		parse_flags(char **av, int ac)
{
	int		i;
	int		k;

	i = 0;
	while ((av[++i] && (k = 1)) && (av[i][0] == '-' && av[i][1]))
		while (av[i][k])
			if (assign_flags(av[i][k++]))
				return (-1);
	if (av[i] && (k = ac - i))
		g_fl->files = &av[i];
	else if ((g_fl->files = (char **)ft_memalloc(sizeof(char *) * 2))
		&& (g_fl->files[0] = ft_strdup("."))
		&& (g_fl->flags.dot = 1))
		k = 0;
	return (k);
}

char					*form_fname(char *name, char *pref_name)
{
	char		*comp_name;
	char		*tmp;

	comp_name = ft_strdup(pref_name);
	tmp = ft_strjoin(comp_name, "/");
	ft_strdel(&comp_name);
	comp_name = ft_strjoin(tmp, name);
	ft_strdel(&tmp);
	return (comp_name);
}

int						main(int ac, char **av)
{
	int			ind;
	char		*env;

	if ((env = getenv("LANG")))
		env = setlocale(LC_ALL, env);
	g_fl = (t_fl *)ft_memalloc(sizeof(t_fl));
	if ((ind = parse_flags(av, ac)) != -1)
	{
		ind ? qsort_ascii_char(g_fl->files, 0, ind - 1) : 1;
		extr_print_sinfo((ind == 0 ? ++ind : ind));
	}
	return (ac);
}
