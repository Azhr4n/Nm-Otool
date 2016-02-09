/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/04 19:26:08 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/04 19:26:09 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include "nm.h"

t_symtab	*get_symtab_c(char *ptr)
{
	struct mach_header_64		*mh;
	struct load_command			*lc;
	int							nb_cmds;
	int							i;

	mh = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*mh);
	nb_cmds = mh->ncmds;
	i = -1;
	while (++i <= nb_cmds)
	{
		if (lc->cmd == LC_SYMTAB)
			return ((struct symtab_command *)lc);
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}

void		get_segment_c(t_segment *seg_c[4], char *ptr)
{
	struct mach_header_64		*mh;
	struct load_command			*lc;
	int							nb_cmds;
	int							i;
	int							j;

	mh = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*mh);
	nb_cmds = mh->ncmds;
	i = -1;
	j = 0;
	while (++i <= nb_cmds)
	{
		if (lc->cmd == LC_SEGMENT_64 || mh->filetype == MH_OBJECT)
		{
			seg_c[j] = (struct segment_command_64 *)lc;
			j++;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}
