/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 22:29:29 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/15 18:16:17 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

#define P_SIZE	6

const size_t	g_mb_perm[P_SIZE] = {S_IWUSR, S_IRUSR, S_IWGRP, S_IRGRP,
	S_IWOTH, S_IROTH};
const char		g_mb_chars[P_SIZE] = "wrwrwr";
const int		g_mb_enums[P_SIZE] = {FL_W, FL_R, FL_W + 3, FL_R + 3,
	FL_W + 6, FL_R + 6};

static inline void	obtain_perm(char *perm, mode_t mode)
{
	int i;

	i = -1;
	while (++i < P_SIZE)
		if (mode & g_mb_perm[i])
			perm[g_mb_enums[i]] = g_mb_chars[i];
	if (mode & S_ISUID && mode & S_IXUSR)
		perm[FL_X_S] = 's';
	else if (mode & S_IXUSR)
		perm[FL_X_S] = 'x';
	else if (mode & S_ISUID)
		perm[FL_X_S] = 'S';
	if (mode & S_ISGID && mode & S_IXGRP)
		perm[FL_X_S + 3] = 's';
	else if (mode & S_IXGRP)
		perm[FL_X_S + 3] = 'x';
	else if (mode & S_ISGID)
		perm[FL_X_S + 3] = 'S';
	if (mode & S_ISVTX && mode & S_IXOTH)
		perm[FL_T] = 't';
	else if (mode & S_IXOTH)
		perm[FL_T] = 'x';
	else if (mode & S_ISVTX)
		perm[FL_T] = 'T';
}

void				print_perm(mode_t mode, char *fullname,
				char *perm, acl_t *acl)
{
	ft_bzero(perm, 13 * sizeof(char));
	ft_memmove(perm, "---------- ", 11);
	if (S_ISCHR(mode))
		perm[P_MODE] = 'c';
	else if (S_ISDIR(mode))
		perm[P_MODE] = 'd';
	else if (S_ISSOCK(mode))
		perm[P_MODE] = 's';
	else if (S_ISFIFO(mode))
		perm[P_MODE] = 'p';
	else if (S_ISBLK(mode))
		perm[P_MODE] = 'b';
	else if (S_ISLNK(mode))
		perm[P_MODE] = 'l';
	else if (S_ISREG(mode))
		perm[P_MODE] = '-';
	obtain_perm(perm, mode);
	doggy_plus(perm, fullname, acl);
	ft_printf("%s ", perm);
}
