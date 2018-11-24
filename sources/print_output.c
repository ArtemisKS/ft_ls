/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:55:00 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/16 19:54:13 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static inline bool		print_dir_name_bl(t_dir *dir_c, t_align *al,
	int fi_num)
{
	if (g_fl->files[1] && fi_num)
		ft_printf("%c%s:\n", fi_num ? '\n' : ++fi_num, dir_c->title);
	if ((g_fl->flags.s || g_fl->flags.mode == 1)
		&& (count_align_dir(dir_c, al)))
		if (dir_c->names && dir_c->names[0])
			ft_printf("total%c%lld\n", ' ', dir_c->blocks_num);
	return (true);
}

static inline int		print_fi_col(t_dir **hdir, int arg_num, t_align *al)
{
	int		i;
	char	*a[MAXNAMLEN];
	t_stat	*b[MAXNAMLEN];
	int		fi_num;

	fi_num = 0;
	i = -1;
	ft_bzero(a, sizeof(char *) * MAXNAMLEN);
	ft_bzero(b, sizeof(t_stat *) * MAXNAMLEN);
	while (++i < arg_num)
		if (hdir[i] && !hdir[i]->dir && ++fi_num &&
			(a[fi_num - 1] = hdir[i]->title))
			b[fi_num - 1] = hdir[i]->tistat;
	if (!(a[fi_num] = NULL) && fi_num)
	{
		b[fi_num] = NULL;
		print_col_output(calc_tab_out(al, a, NULL), a, b, *al);
	}
	return (fi_num);
}

static inline int		print_files(t_dir **hdir, int arg_num, t_align *al)
{
	int		fi_num;
	int		i;

	fi_num = 0;
	i = -1;
	if (g_fl->flags.mode)
	{
		while (++i < arg_num)
			if (hdir[i] && !hdir[i]->dir && ++fi_num)
				print_ls_arg(hdir[i]->tistat, hdir[i]->title, NULL, *al);
	}
	else
		fi_num = print_fi_col(hdir, arg_num, al);
	return (fi_num);
}

static inline int		print_ftitles(t_dir **hdir, int arg_num)
{
	int				i;
	t_align			align;
	int				fi_num;

	if (g_fl->flags.s || g_fl->flags.mode == 1)
	{
		i = -1;
		ft_bzero(&align, sizeof(int) * AL_F_NUM);
		while (++i < arg_num)
			if (hdir[i] && !hdir[i]->dir)
				assign_al(hdir[i]->tistat, &align);
	}
	fi_num = print_files(hdir, arg_num, &align);
	return (fi_num);
}

void					print_args(t_dir **hdir, int arg_num)
{
	int				i;
	int				j;
	int				fi_num;
	t_align			al;

	fi_num = print_ftitles(hdir, arg_num);
	i = -1;
	while (++i < arg_num)
		if (hdir[i] && hdir[i]->dir)
		{
			if (!g_fl->flags.cap_r && ((j = -1) == -1)
			&& (print_dir_name_bl(hdir[i], &al, fi_num)))
				while (hdir[i]->names[++j])
				{
					if (!g_fl->flags.mode && print_col_output(calc_tab_out(&al,
					hdir[i]->names, hdir[i]->stat), hdir[i]->names,
					hdir[i]->stat, al))
						break ;
					else
						print_ls_arg(hdir[i]->stat[j], hdir[i]->names[j],
							hdir[i]->title, al);
				}
			else
				print_cap_r(NULL, hdir[i]->title);
		}
}
