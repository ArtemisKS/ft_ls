/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_al.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:41:40 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/16 20:11:52 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static inline void	assign_al_if_s(t_stat *s, t_align *tal, t_align tmp)
{
	int			i;

	if (g_fl->flags.mode == 1 && (i = 10))
	{
		while (s->st_size / i && (++tmp.tsize_al))
			i *= 10;
		i = 10;
		(tal->tsize_al < tmp.tsize_al) ? tal->tsize_al = tmp.tsize_al : 1;
		while (s->st_ino / i && (++tmp.inode_al))
			i *= 10;
		(tal->inode_al < tmp.inode_al) ? tal->inode_al = tmp.inode_al : 1;
	}
	if (g_fl->flags.s && (i = 10))
	{
		while (s->st_blocks / i && (++tmp.block_al))
			i *= 10;
		(tal->block_al < tmp.block_al) ? tal->block_al = tmp.block_al : 1;
	}
}

void				assign_al(t_stat *s, t_align *al)
{
	t_passwd	*pas;
	t_group		*gr;
	t_align		t_al;
	int			i;
	static bool	fl = false;

	ft_bzero(&t_al, sizeof(int) * AL_F_NUM);
	if (g_fl->flags.mode == 1 && (i = 10))
	{
		while (s->st_nlink / i && (++t_al.hlinks_al))
			i *= 10;
		(al->hlinks_al < t_al.hlinks_al) ? al->hlinks_al = t_al.hlinks_al : 1;
		(!(pas = getpwuid(s->st_uid))) ? errno_exit(true, true) : 1;
		(!(gr = getgrgid(s->st_gid))) ? errno_exit(true, true) : 1;
		if (al->user_al < (t_al.user_al = ft_strlen(pas->pw_name)))
			al->user_al = t_al.user_al;
		if (al->group_al < (t_al.group_al = ft_strlen(gr->gr_name)))
			al->group_al = t_al.group_al;
		if ((S_ISCHR(s->st_mode) || S_ISBLK(s->st_mode)) && !fl && (fl = 1))
			al->tsize_al += 4;
	}
	assign_al_if_s(s, al, t_al);
}

void				qsort_swap(t_dir *dir_c, int *i, int *j)
{
	ft_swap(&(dir_c->stat[*i]), &(dir_c->stat[*j]));
	ft_swap(&(dir_c->names[(*i)++]), &(dir_c->names[(*j)--]));
}
