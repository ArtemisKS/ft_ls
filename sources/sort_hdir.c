/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_hdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:42:09 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/16 20:12:48 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

#define A_T(x, y)	(y ? hdir[x]->tistat->st_atime : hdir[x]->tistat->st_mtime)
#define IND			(ind - lines)
#define SP_M		(tcol.len - ft_strlen(ns[IND]))
#define SP_NUM(f)	(f ? SP_M : SP_M - 1)
#define F_COND		(g_fl->flags.p && (S_ISDIR(st[IND]->st_mode)))
#define S_COND		(g_fl->flags.p && al.dnum < num / 2)

static inline size_t		ft_arlen(void **arr)
{
	size_t	len;

	len = -1;
	if (arr && *arr)
		while (arr[++len])
			;
	return (len);
}

void						sort_arg_time(t_dir **hdir, int arg_num)
{
	int			i;
	int			ind;
	t_dir		*str;

	i = -1;
	ind = 0;
	while ((++i) < arg_num - 1)
	{
		if (hdir[i] && hdir[i + 1] && (g_fl->flags.r ? A_T(i, g_fl->flags.u)
		> A_T(i + 1, g_fl->flags.u) : A_T(i, g_fl->flags.u)
		< A_T(i + 1, g_fl->flags.u)))
		{
			str = hdir[i];
			hdir[i] = hdir[i + 1];
			hdir[i + 1] = str;
			ind++;
		}
	}
	if (ind)
		sort_arg_time(hdir, arg_num);
}

bool						print_col_output(t_col tcol, char **ns,
	t_stat **st, t_align al)
{
	int		i;
	int		j;
	int		num;
	int		lines;
	int		ind;

	if (!tcol.len || (num = ft_arlen((void **)ns)) == -1)
		return (true);
	lines = num / tcol.col_num + (num % tcol.col_num ? 1 : 0);
	i = -1;
	while (++i < lines)
	{
		j = 0;
		ind = i + j * lines;
		while (ind < num)
		{
			print_ls_arg(st[ind], ns[ind], NULL, tcol.al);
			ind += lines;
			if (++j < tcol.col_num && ind < num)
				ft_printf("%*c", SP_NUM(F_COND || S_COND
				|| !g_fl->flags.p), ' ');
		}
		ft_putchar('\n');
	}
	return (true);
}

void						sort_arg_ascii(t_dir **hdir, int arg_num)
{
	int			i;
	int			ind;
	t_dir		*str;

	i = -1;
	ind = 0;
	while ((++i) < arg_num - 1)
	{
		if (hdir[i] && hdir[i + 1] && (g_fl->flags.r ?
		ft_strcmp(hdir[i]->title, hdir[i + 1]->title) < 0
		: ft_strcmp(hdir[i]->title, hdir[i + 1]->title) > 0))
		{
			str = hdir[i];
			hdir[i] = hdir[i + 1];
			hdir[i + 1] = str;
			ind++;
		}
	}
	if (ind)
		sort_arg_ascii(hdir, arg_num);
}
