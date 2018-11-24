/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_xattr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:54:28 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/15 20:00:10 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void						qsort_ascii_char(char **files, int left, int right)
{
	int			i;
	int			j;
	char		*param;

	i = left;
	j = right;
	param = files[(left + right) / 2];
	while (i <= j)
	{
		while ((g_fl->flags.r ? ft_strcmp(files[i], param) > 0
		: ft_strcmp(files[i], param) < 0) && i < right)
			i++;
		while ((g_fl->flags.r ? ft_strcmp(param, files[j]) > 0
		: ft_strcmp(param, files[j]) < 0) && j > left)
			j--;
		if (i <= j)
			ft_swap(&files[i++], &files[j--]);
	}
	if (i < right)
		qsort_ascii_char(files, i, right);
	if (left < j)
		qsort_ascii_char(files, left, j);
}

void						doggy_plus(char *perm, char *comp_name, acl_t *acl)
{
	acl_entry_t	acl_entry;
	ssize_t		s_xattrlst;

	*acl = acl_get_link_np(comp_name, ACL_TYPE_EXTENDED);
	if (*acl && acl_get_entry(*acl, ACL_FIRST_ENTRY, &acl_entry) == -1)
	{
		acl_free(*acl);
		*acl = NULL;
	}
	if ((s_xattrlst = listxattr(comp_name, NULL, 0, XATTR_NOFOLLOW)) == -1)
		errno_exit(false, false);
	if (s_xattrlst > 0)
		perm[AT_POS] = AT;
	else if (s_xattrlst < 0)
		errno_exit(false, false);
	else if (*acl)
		perm[AT_POS] = PL;
	if (*acl)
		perm[PL_POS] = PL;
}

void						print_ext_attr(char *cname)
{
	ssize_t		llen;
	char		lst[XATTR_MAXNAMELEN];
	ssize_t		glen;
	int			attr_al;

	attr_al = 0;
	if ((llen = listxattr(cname, lst, XATTR_MAXNAMELEN, XATTR_NOFOLLOW)) > 0)
		while (attr_al < llen)
		{
			glen = getxattr(cname, &lst[attr_al], NULL, 0, 0, XATTR_NOFOLLOW);
			ft_printf("\t%s\t  %zd \n", &lst[attr_al], glen);
			attr_al += ft_strlen(&lst[attr_al]) + 1;
		}
	else
		errno_exit(false, false);
}

void						print_pl_acl(acl_t acl)
{
	char		*str;
	char		**mdata;
	int			i;

	i = -1;
	if ((str = acl_to_text(acl, NULL)))
	{
		mdata = ft_strsplit(ft_strchr(str, '\n') + 1, ':');
		ft_printf(" 0: %s:%s %s %s", mdata[0], mdata[2], mdata[4], mdata[5]);
		ft_strdel(&str);
		while (mdata[++i])
			ft_strdel(&mdata[i]);
		free(mdata);
	}
	acl_free(acl);
}
