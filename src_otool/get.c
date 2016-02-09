/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/04 19:28:51 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/04 19:28:51 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include "otool.h"
#include "tools.h"

t_segment	*get_segment(void *ptr)
{
	struct mach_header_64		*mh;
	struct load_command			*lc;
	t_segment					*seg_c;
	int							nb_cmds;
	int							i;

	mh = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*mh);
	nb_cmds = mh->ncmds;
	i = -1;
	while (++i <= nb_cmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg_c = (struct segment_command_64 *)lc;
			if (!ft_strcmp(seg_c->segname, "__TEXT")
				|| mh->filetype == MH_OBJECT)
				return (seg_c);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}

void		special_print(char *str, int option, int val)
{
	int		i;

	i = 0;
	while (str[i] && val > 0)
	{
		ft_putchar(str[i]);
		if (i != 0 && i % 2 != 0)
			ft_putstr(" ");
		if ((i % 2))
			val--;
		i++;
	}
	if (option)
		ft_putchar('\n');
}
