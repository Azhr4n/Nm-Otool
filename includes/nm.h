/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 15:50:08 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/02 15:50:09 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define TEXT 1
# define DATA 2

typedef struct symtab_command		t_symtab;
typedef struct segment_command_64	t_segment;

typedef struct	s_sort
{
	char		*type;
	char		*value;
	char		*symbol;
}				t_sort;

void			fill_struct(t_symtab *sym_c, t_segment *seg_c[4], void *ptr);
void			get_segment_c(t_segment *seg_c[4], char *ptr);

t_symtab		*get_symtab_c(char *ptr);

#endif
