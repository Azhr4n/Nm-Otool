/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 17:02:01 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/02 17:02:01 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include "tools.h"
#include "nm.h"

static void	sort_struct(t_symtab *sym_c, t_sort *sym)
{
	t_sort			tmp;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < sym_c->nsyms - 1)
	{
		j = i + 1;
		while (j < sym_c->nsyms)
		{
			if (ft_strcmp(sym[i].symbol, sym[j].symbol) > 0)
			{
				tmp = sym[i];
				sym[i] = sym[j];
				sym[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print(t_symtab *sym_c, t_sort *sym, t_segment **seg_c)
{
	unsigned int	i;

	(void)seg_c;
	i = 0;
	sort_struct(sym_c, sym);
	while (i < sym_c->nsyms)
	{
		ft_putstr(sym[i].value);
		ft_putstr(sym[i].type);
		ft_putstr(sym[i].symbol);
		ft_putstr("\n");
		i++;
	}
}

void		set_type(struct nlist_64 *tab, t_segment *seg_c[4], t_sort *sym,
	int nseg)
{
	struct section_64	*sec;
	unsigned int		i;

	if (nseg > 2)
	{
		i = 0;
		sec = (void *)seg_c[2] + sizeof(t_segment);
		while (i < seg_c[2]->nsects)
		{
			if (!(ft_strcmp(sec->sectname, "__bss"))
				&& ((tab[i].n_type & 0x01) == N_EXT))
				sym->type = " B ";
			else if (!(ft_strcmp(sec->sectname, "__bss"))
				&& ((tab[i].n_type & 0x01) != N_EXT))
				sym->type = " b ";
			else if ((tab[i].n_type & 0x01) == N_EXT)
				sym->type = " S ";
			else
				sym->type = " s ";
			sec = (void *)sec + sizeof(struct section_64);
			i++;
		}
	}
}

void		fill_struct(t_symtab *sym_c, t_segment *seg_c[4], void *ptr)
{
	t_sort						sym[sym_c->nsyms];
	struct nlist_64				*tab;
	unsigned int				i;

	tab = ptr + sym_c->symoff;
	i = -1;
	while (++i < sym_c->nsyms)
	{
		if (tab[i].n_value || (tab[i].n_sect))
			sym[i].value = b_to_h(d_to_b(tab[i].n_value), "0123456789abcdef");
		else
			sym[i].value = "";
		if (tab[i].n_sect == TEXT && (tab[i].n_type & 0x01) == N_EXT)
			sym[i].type = " T ";
		else if (tab[i].n_sect == TEXT && (tab[i].n_type & 0x01) != N_EXT)
			sym[i].type = " t ";
		else if (tab[i].n_sect >= DATA && (tab[i].n_type & 0x01) == N_EXT)
			sym[i].type = " S ";
		else if (tab[i].n_sect >= DATA && (tab[i].n_type & 0x01) != N_EXT)
			sym[i].type = " s ";
		else
			sym[i].type = "                 U ";
		sym[i].symbol = (char *)(ptr + sym_c->stroff + tab[i].n_un.n_strx);
	}
	print(sym_c, sym, seg_c);
}
