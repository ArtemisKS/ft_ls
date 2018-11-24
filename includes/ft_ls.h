/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:25:19 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/16 19:54:04 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <libftprintf.h>
# include <sys/types.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include <uuid/uuid.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <locale.h>

# define BUFF_SIZE			4096
# define PL					'+'
# define AT 				'@'
# define PL_POS				12
# define AT_POS				10
# define AL_F_NUM			7
# define I(x)				(x + 1)
# define RESET				"\033[0m"
# define B_CYAN				"\033[1;36m"
# define B_YELLOW			"\033[1;33m"
# define BLUE				"\033[0;34m"
# define YELLOW				"\033[0;33m"
# define GREEN				"\033[0;32m"
# define PURPLE				"\033[0;35m"
# define RED				"\033[0;31m"
# define TIME_FILES(a, b)	(b == 1 ? files[a]->st_atime : files[a]->st_mtime)
# define GET_TIME(y)		(y == 1 ? file->st_atime : file->st_mtime)

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_align
{
	int					block_al;
	int					hlinks_al;
	int					user_al;
	int					group_al;
	int					tsize_al;
	int					inode_al;
	int					dnum;
}						t_align;

typedef struct			s_flags
{
	char				cap_g;
	char				cap_r;
	char				a;
	char				e;
	char				i;
	char				p;
	char				r;
	char				s;
	char				t;
	char				u;
	char				at;
	char				mode;
	char				dot;
	char				cap_a;
	char				d;
	char				f;
	char				g;
}						t_flags;

typedef struct			s_fl
{
	t_flags				flags;
	char				**files;
}						t_fl;

typedef enum			e_penum
{
	P_MODE = 0,
	FL_R,
	FL_W,
	FL_X_S,
	FL_T = 9,
}						t_penum;

t_fl					*g_fl;

typedef struct			s_dir
{
	char				*title;
	t_stat				*tistat;
	int					dm;
	DIR					*dir;
	char				**names;
	t_stat				**stat;
	u_quad_t			blocks_num;
}						t_dir;

typedef struct			s_col
{
	size_t				len;
	int					col_num;
	t_align				al;
}						t_col;

void					qsort_swap(t_dir *dir_c, int *i, int *j);
char					*form_fname(char *name, char *pref_name);
t_col					calc_tab_out(t_align *al, char **names, t_stat **stat);
void					print_pl_acl(acl_t acl);
void					print_ext_attr(char *comp_name);
void					errno_exit(bool to_print, bool to_exit);
void					doggy_plus(char *perm, char *comp_name, acl_t *acl);
void					print_perm(mode_t mode, char *comp_name,
						char *perm, acl_t *acl);
void					print_time(t_stat *s);
void					colored_print(t_stat *s);
void					assign_al(t_stat *s, t_align *al);
bool					count_align_dir(t_dir *dir_c, t_align *al);
t_dir					*open_read(char *name);
bool					print_col_output(t_col tcol, char **ns, t_stat **st,
	t_align al);
void					do_sorting(t_dir *dir_c, t_dir **hdir, int arg_num);
void					sort_arg_time(t_dir **hdir, int arg_num);
void					qsort_ascii_char(char **files, int left,
						int right);
void					print_ls_arg(t_stat *s, char *filename,
						char *pref_name, t_align al);
void					print_lstat(t_stat *s, char *filename, char *pref_name,
						t_align al);
void					print_args(t_dir **hdir, int arg_num);
void					sort_arg_ascii(t_dir **hdir, int arg_num);
void					extr_print_sinfo(int arg_num);
void					print_cap_r(char *pref_name, char *filename);

#endif
