/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sorting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:52:13 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/15 19:01:41 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

#define F_TM(a, b)	(b == 1?dir_c->stat[a]->st_atime:dir_c->stat[a]->st_mtime)

static inline void		qsort_date(t_stat **files, int left, int right,
	t_dir *dir_c)
{
	int			i;
	int			j;
	t_stat		*file;

	i = left;
	j = right;
	file = files[(left + right) / 2];
	while (i <= j)
	{
		while ((g_fl->flags.r ? GET_TIME(g_fl->flags.u)
		< TIME_FILES(j, g_fl->flags.u) : GET_TIME(g_fl->flags.u)
		> TIME_FILES(j, g_fl->flags.u)) && j > left)
			j--;
		while ((g_fl->flags.r ? TIME_FILES(i, g_fl->flags.u)
		< GET_TIME(g_fl->flags.u) : TIME_FILES(i, g_fl->flags.u)
		> GET_TIME(g_fl->flags.u)) && i < right)
			i++;
		if (i <= j)
			qsort_swap(dir_c, &i, &j);
	}
	if (i < right)
		qsort_date(files, i, right, dir_c);
	if (left < j)
		qsort_date(files, left, j, dir_c);
}

static inline void		qsort_ascii(char **files, int left, int right,
	t_dir *dir_c)
{
	int			i;
	int			j;
	char		*file;

	i = left;
	j = right;
	file = files[(left + right) / 2];
	while (i <= j)
	{
		while ((g_fl->flags.r ? ft_strcmp(file, files[j]) > 0
		: ft_strcmp(file, files[j]) < 0) && j > left)
			j--;
		while ((g_fl->flags.r ? ft_strcmp(files[i], file) > 0
		: ft_strcmp(files[i], file) < 0) && i < right)
			i++;
		if (i <= j)
			qsort_swap(dir_c, &i, &j);
	}
	if (i < right)
		qsort_ascii(files, i, right, dir_c);
	if (left < j)
		qsort_ascii(files, left, j, dir_c);
}

static inline void		qsort_date_ascii(t_dir *dir_c)
{
	int			i;
	int			j;

	i = 0;
	while (dir_c->stat[i] && dir_c->stat[i + 1])
	{
		if (F_TM(i, g_fl->flags.u) == F_TM(i + 1, g_fl->flags.u))
		{
			j = i;
			while (dir_c->stat[j] && dir_c->stat[j + 1] &&
			(F_TM(j, g_fl->flags.u) == F_TM(j + 1, g_fl->flags.u)))
				j++;
			qsort_ascii(dir_c->names, i, j, dir_c);
		}
		i++;
	}
}

void					do_sorting(t_dir *dir_c, t_dir **hdir, int argn)
{
	if (g_fl->flags.f)
		return ;
	if (hdir)
	{
		sort_arg_ascii(hdir, argn);
		g_fl->flags.t ? sort_arg_time(hdir, argn) : 1;
	}
	else if (dir_c)
	{
		if (g_fl->flags.t && dir_c->stat)
		{
			qsort_date(dir_c->stat, 0, dir_c->dm - 1, dir_c);
			qsort_date_ascii(dir_c);
		}
		else if (dir_c->names)
			qsort_ascii(dir_c->names, 0, dir_c->dm - 1, dir_c);
	}
}
