/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cap_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 21:00:47 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/16 20:10:56 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static inline void		print_dir_name_rec(bool flag, char *n)
{
	if (flag)
		ft_printf("%c%s:\n", '\n', (n[0] == '/' && n[1] == '/' ? n + 1 : n));
	else if (g_fl->files[1])
		ft_printf("%s:\n", (n[0] == '/' && n[1] == '/' ? n + 1 : n));
}

static inline void		print_cdir_rec(t_dir *dir_c, char *com_name)
{
	t_align		tal;
	int			i;

	i = -1;
	if ((g_fl->flags.s || g_fl->flags.mode == 1)
		&& (count_align_dir(dir_c, &tal)))
		if (dir_c->names && dir_c->names[0])
			ft_printf("total%c%lld\n", ' ', dir_c->blocks_num);
	if (!g_fl->flags.mode)
		print_col_output(calc_tab_out(&tal, dir_c->names, dir_c->stat),
			dir_c->names, dir_c->stat, tal);
	else
		while (dir_c->names[++i])
			print_ls_arg(dir_c->stat[i], dir_c->names[i], com_name, tal);
}

static inline bool		d_memdel(t_dir *dir_c, char *comp_name, char *filename)
{
	int			ind;

	ind = -1;
	(comp_name != filename) ? ft_strdel(&comp_name) : 1;
	if (!dir_c)
		return (true);
	(dir_c->tistat) ? ft_memdel((void **)&dir_c->tistat) : 1;
	(dir_c->title) ? ft_strdel(&dir_c->title) : 1;
	if (dir_c->dir)
	{
		while (dir_c->names[++ind])
		{
			ft_memdel((void **)&dir_c->stat[ind]);
			ft_strdel(&dir_c->names[ind]);
		}
		free(dir_c->stat);
		free(dir_c->names);
	}
	ft_memdel((void **)&dir_c);
	return (true);
}

void					print_cap_r(char *prename, char *filename)
{
	t_dir		*dir;
	char		*com_name;
	static bool	flag = false;
	int			i;

	i = -1;
	com_name = (prename ? form_fname(filename, prename) : filename);
	print_dir_name_rec(flag, com_name);
	if (!(dir = open_read(com_name)) && d_memdel(dir, com_name, filename))
		return ;
	print_cdir_rec(dir, com_name);
	while (dir->names[++i])
		if ((flag = true) && dir->stat[i] && S_ISDIR(dir->stat[i]->st_mode)
		&& !ft_strequ(dir->names[i], ".") && !ft_strequ(dir->names[i], ".."))
			print_cap_r(com_name, dir->names[i]);
	d_memdel(dir, com_name, filename);
}
