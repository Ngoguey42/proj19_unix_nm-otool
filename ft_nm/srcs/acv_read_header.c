/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acv_read_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:05:20 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/15 17:49:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
** #1/20           1455545839  9273  4215  100644  92        `$
** Offset	Length	Name				Format
** 0		16		File name			ASCII
** 16		12		File modification	timestampDecimal
** 28		6		Owner				IDDecimal
** 34		6		Group				IDDecimal
** 40		8		File				modeOctal
** 48		10		File size in bytes	Decimal
** 58		2		File magic			0x60 0x0A
*/

static bool		range_uinteger(char const *ptr, size_t len, size_t dst[1])
{
	char const *const	save = ptr;

	*dst = 0;
	while (len > 0 && ft_isdigit(*ptr))
	{
		*dst = *dst * 10 + *ptr - '0';
		len--;
		ptr++;
	}
	if (save == ptr)
		return (false);
	while (len > 0 && *ptr == ' ')
	{
		len--;
		ptr++;
	}
	if (len != 0)
		return (false);
	return (true);
}

static int		parse_name_data(t_bininfo const bi[1], t_acvinfo ai[1],
						   void const *const ptr, size_t tmp[1])
{
	char const	*tmpptr;

	if (ft_memcmp(ptr, "#1/", 3) == 0)
	{
		if (!range_uinteger(ptr + 3, 16 - 3, tmp))
			return (1);
		ai->filename.str = ptr + 60;
		tmpptr = ft_strchr(ai->filename.str, '\0');
		if (tmpptr == NULL)
			ai->filename.len = *tmp;
		else
			ai->filename.len = tmpptr - ai->filename.str;
		if (!nm_bin_ckaddr(bi, ai->filename.str, *tmp))
			return (ERRORF("mmap overflow"));
		ai->data = ptr + 60 + *tmp;
	}
	else
	{
		ai->filename.str = ptr;
		ai->filename.len = 16;
		ai->data = ptr + 60;
	}
	return (0);
}

int		nm_acv_read_header(t_bininfo const bi[1], t_acvinfo ai[1])
{
	void const *const	ptr = ai->hdr;
	size_t				tmp[1];

	if (parse_name_data(bi, ai, ptr, tmp))
		return (1);
	if (!nm_bin_ckaddr(bi, ptr, 60))
		return (ERRORF("mmap overflow"));
	if (!range_uinteger(ptr + 16, 12, tmp))
		return (1);
	if (!range_uinteger(ptr + 28, 6, tmp))
		return (1);
	if (!range_uinteger(ptr + 34, 6, tmp))
		return (1);
	if (!range_uinteger(ptr + 40, 8, tmp))
		return (1);
	if (!range_uinteger(ptr + 48, 10, tmp))
		return (1);
	ai->filesize = *tmp;
	if (!nm_bin_ckaddr(bi, ptr, ai->filesize))
		return (ERRORF("mmap overflow"));
	if (ft_memcmp(ptr + 58, "`\n", 2) != 0)
		return (1);
	return (0);
}
