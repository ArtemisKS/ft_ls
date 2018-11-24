/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:15:05 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/15 19:18:00 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static inline void		read_dir_stat(char *name, t_dir *dir_a)
{
	char		*fname;
	int			i;

	i = -1;
	dir_a->stat = (t_stat **)ft_memalloc(sizeof(t_stat *) * (dir_a->dm + 1));
	while (dir_a->names[++i])
	{
		dir_a->stat[i] = (t_stat *)ft_memalloc(sizeof(t_stat));
		fname = form_fname(dir_a->names[i], name);
		lstat(fname, dir_a->stat[i]);
		ft_strdel(&fname);
	}
	dir_a->stat[i] = NULL;
}

static inline int		open_read_dir(char *name, t_dir *dir_a)
{
	t_dirent	*dir_cont;
	int			i;

	i = 0;
	if (!(dir_a->dir = opendir(name)))
		return (-1);
	while ((dir_cont = readdir(dir_a->dir)))
		i++;
	rewinddir(dir_a->dir);
	dir_a->names = (char **)ft_memalloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((dir_cont = readdir(dir_a->dir)))
	{
		if ((!g_fl->flags.a && dir_cont->d_name[0] == '.') ||
		(g_fl->flags.cap_a && (ft_strequ(dir_cont->d_name, ".") ||
		ft_strequ(dir_cont->d_name, ".."))))
			continue ;
		dir_a->names[i++] = ft_strdup(dir_cont->d_name);
	}
	dir_a->dm = i;
	dir_a->names[dir_a->dm] = NULL;
	return (closedir(dir_a->dir));
}

static inline char		*crop_slash(char *name)
{
	int		i;

	i = ft_strlen(name);
	while (name[--i] != '/' && i)
		;
	return (i ? (name + ++i) : (name));
}

static inline bool		bool_free(void *fl)
{
	if (fl)
		ft_memdel(&fl);
	return (1);
}

t_dir					*open_read(char *name)
{
	t_dir		*dir_a;
	t_stat		*tstat;

	tstat = (t_stat *)ft_memalloc(sizeof(t_stat));
	if (lstat(name, tstat) == -1 && bool_free(tstat) &&
	ft_dprintf(2, "./ft_ls: %s: %s\n", crop_slash(name), strerror(errno)))
		return (NULL);
	dir_a = (t_dir *)ft_memalloc(sizeof(t_dir));
	dir_a->title = ft_strdup(name);
	dir_a->tistat = tstat;
	if (!g_fl->flags.d && S_ISDIR(dir_a->tistat->st_mode))
	{
		if (open_read_dir(name, dir_a))
		{
			ft_dprintf(2, "./ft_ls: %s: %s\n", crop_slash(name),
			strerror(errno));
			ft_strdel(&dir_a->title);
			ft_memdel((void **)&dir_a->tistat);
			ft_memdel((void **)&dir_a);
			return (NULL);
		}
		read_dir_stat(name, dir_a);
		do_sorting(dir_a, NULL, 0);
	}
	return (dir_a);
}
