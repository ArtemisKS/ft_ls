/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lstat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 23:08:54 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/15 21:27:50 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

#define DOW_SIZE	4

static inline void	print_fname(t_stat *s, char *comp_name, char *fname,
	bool is_dir)
{
	char		*str;

	g_fl->flags.cap_g ? colored_print(s) : 1;
	if (!S_ISLNK(s->st_mode))
	{
		ft_printf("%s%s", fname, g_fl->flags.cap_g ? RESET : "");
		ft_printf((is_dir) ? "/\n" : "\n");
	}
	else
	{
		str = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
		if (readlink(comp_name, str, BUFF_SIZE) != -1)
		{
			ft_printf("%s%s", fname, g_fl->flags.cap_g ? RESET : "");
			ft_printf(" -> %s\n", str);
		}
		ft_strdel(&str);
	}
}

static inline void	print_own_gr_size(t_stat *st, t_align align, char *perm)
{
	t_passwd	*passwd;
	t_group		*group;
	long		minor;
	long		major;

	if (!g_fl->flags.g)
		if ((passwd = getpwuid(st->st_uid)))
			ft_printf("%-*s ", I(align.user_al), passwd->pw_name);
	if ((group = getgrgid(st->st_gid)))
		ft_printf("%-*s ", I(align.group_al), group->gr_name);
	if (perm[0] == 'b' || perm[0] == 'c')
	{
		major = (long)major(st->st_rdev);
		minor = (long)minor(st->st_rdev);
		major <= 128 ? ft_printf("%3ld, ", major)
			: ft_printf("%#3.8lx, ", major);
		minor <= 128 ? ft_printf("%3ld ", minor)
			: ft_printf("%#3.8lx ", minor);
	}
	else
		ft_printf("%*lu ", I(align.tsize_al), (unsigned long)st->st_size);
}

void				print_lstat(t_stat *s, char *fname, char *pref_name,
	t_align align)
{
	acl_t		acl;
	char		perm[13];
	char		*comp_name;

	comp_name = (pref_name ? form_fname(fname, pref_name) : fname);
	g_fl->flags.i ? ft_printf("%*lu ", I(align.inode_al),
			(unsigned long)s->st_ino) : 1;
	g_fl->flags.s ? ft_printf("%*lu ", I(align.block_al),
		(unsigned long)s->st_blocks) : 1;
	print_perm(s->st_mode, comp_name, perm, &acl);
	ft_printf("%*lu ", I(align.hlinks_al), (unsigned long)s->st_nlink);
	print_own_gr_size(s, align, perm);
	print_time(s);
	print_fname(s, comp_name, fname, (S_ISDIR(s->st_mode)) && g_fl->flags.p);
	(perm[AT_POS] == AT && g_fl->flags.at) ? print_ext_attr(comp_name) : 1;
	if (perm[PL_POS] == PL && g_fl->flags.e)
		print_pl_acl(acl);
	else if (acl)
		acl_free(acl);
	(pref_name) ? ft_strdel(&comp_name) : 1;
}
