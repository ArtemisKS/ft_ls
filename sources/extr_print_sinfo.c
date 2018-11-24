/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extr_print_sinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:58:40 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/16 20:12:07 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static inline void		memdel_cdir(t_dir **dir_c, int arg_num)
{
	int			i;
	int			j;

	i = -1;
	while (++i < arg_num)
	{
		if (!dir_c[i])
			continue ;
		ft_memdel((void **)&dir_c[i]->tistat);
		ft_strdel(&dir_c[i]->title);
		j = -1;
		if (dir_c[i]->dir)
		{
			while (dir_c[i]->names[++j])
			{
				ft_memdel((void **)&dir_c[i]->stat[j]);
				ft_strdel(&dir_c[i]->names[j]);
			}
			free(dir_c[i]->stat);
			free(dir_c[i]->names);
		}
		ft_memdel((void **)&dir_c[i]);
	}
	free(dir_c);
}

static inline int		calc_mlen(t_align *al, char **names, t_stat **stat,
	bool a_fl)
{
	int		max;
	int		nlen;
	int		i;
	int		len;

	max = -1;
	i = -1;
	nlen = 0;
	while (names[++i])
	{
		g_fl->flags.i && a_fl ? nlen += I(al->inode_al) : 1;
		g_fl->flags.s && a_fl ? nlen += I(al->block_al) : 1;
		len = ft_strlen(names[i]);
		(stat && g_fl->flags.p && (S_ISDIR(stat[i]->st_mode)))
			? al->dnum++ : 1;
		((nlen += len) > max) ? max = nlen : 1;
		nlen = 0;
	}
	return (++max);
}

t_col					calc_tab_out(t_align *al, char **names, t_stat **stat)
{
	size_t			t_width;
	struct winsize	tts;
	t_col			tcol;

	al->dnum = 0;
	ft_bzero(&tcol, sizeof(t_col *));
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &tts);
	t_width = tts.ws_col;
	tcol.len = calc_mlen(al, names, stat, true);
	if (!tcol.len)
		return (tcol);
	(g_fl->flags.p) ? tcol.len++ : 1;
	tcol.col_num = (tcol.len > t_width) ? (1) : (t_width / tcol.len);
	if (g_fl->flags.i || g_fl->flags.s)
		tcol.len = calc_mlen(al, names, stat, false);
	tcol.al = *al;
	return (tcol);
}

void					extr_print_sinfo(int arg_num)
{
	t_dir		**dir_c;
	int			i;

	i = -1;
	dir_c = (t_dir **)ft_memalloc(sizeof(t_dir *) * (arg_num + 1));
	while (++i < arg_num)
		dir_c[i] = open_read(g_fl->files[i]);
	do_sorting(NULL, dir_c, arg_num);
	print_args(dir_c, arg_num);
	memdel_cdir(dir_c, arg_num);
}
