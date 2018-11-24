/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:39:47 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/15 21:26:58 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

#define MAXC 64

void					print_time(t_stat *s)
{
	char	t_str[MAXC];
	char	*env;

	env = setlocale(LC_ALL, NULL);
	if (g_fl->flags.u)
		strftime(t_str, sizeof(t_str), ft_strequ(env, "ru_RU.UTF-8")
		? "%e %b %H:%M" : "%b %e %H:%M",
		localtime((const time_t *)&s->st_atime));
	else
		strftime(t_str, sizeof(t_str), ft_strequ(env, "ru_RU.UTF-8")
		? "%e %b %H:%M" : "%b %e %H:%M",
		localtime((const time_t *)&s->st_mtime));
	ft_printf("%s ", t_str);
}

void					errno_exit(bool to_print, bool to_exit)
{
	char *error;

	error = strerror(errno);
	if (to_print)
		ft_dprintf(2, "./ft_ls: %s\n", error);
	if (to_exit)
		exit(1);
}

void					colored_print(t_stat *s)
{
	if (S_ISFIFO(s->st_mode))
		ft_printf(B_YELLOW);
	else if (S_ISDIR(s->st_mode))
		ft_printf(B_CYAN);
	else if (S_ISBLK(s->st_mode))
		ft_printf(BLUE);
	else if (S_ISCHR(s->st_mode))
		ft_printf(YELLOW);
	else if (S_ISSOCK(s->st_mode))
		ft_printf(GREEN);
	else if (S_ISLNK(s->st_mode))
		ft_printf(PURPLE);
	else if (S_ISREG(s->st_mode) && (s->st_mode & S_IXUSR
	|| s->st_mode & S_IXOTH || s->st_mode & S_IXGRP))
		ft_printf(RED);
}

bool					count_align_dir(t_dir *dir_c, t_align *align)
{
	int		i;

	i = -1;
	ft_bzero(align, sizeof(int) * AL_F_NUM);
	dir_c->blocks_num = 0;
	while (dir_c->stat[++i])
	{
		assign_al(dir_c->stat[i], align);
		dir_c->blocks_num += dir_c->stat[i]->st_blocks;
	}
	return (true);
}

void					print_ls_arg(t_stat *s, char *fname, char *pref_name,
	t_align align)
{
	if (g_fl->flags.mode == 1)
		print_lstat(s, fname, pref_name, align);
	else
	{
		g_fl->flags.i ? ft_printf("%*lu ", I(align.inode_al),
			(unsigned long)s->st_ino) : 1;
		g_fl->flags.s ? ft_printf("%*lu ", I(align.block_al),
			(unsigned long)s->st_blocks) : 1;
		g_fl->flags.cap_g ? colored_print(s) : 1;
		ft_printf("%s%s", fname, g_fl->flags.cap_g ? RESET : "");
		if (S_ISDIR(s->st_mode) && g_fl->flags.p)
			(g_fl->flags.mode) ? ft_printf("/\n") : ft_putchar('/');
		else
			(g_fl->flags.mode) ? ft_printf("\n") : 1;
	}
}
