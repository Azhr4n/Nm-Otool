/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/30 12:26:32 by pivanovi          #+#    #+#             */
/*   Updated: 2014/09/30 12:26:33 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "tools.h"
#include "nm.h"

void		handle_64(char *ptr)
{
	t_symtab	*sym_c;
	t_segment	*seg_c[4];

	sym_c = get_symtab_c(ptr);
	get_segment_c(seg_c, ptr);
	fill_struct(sym_c, seg_c, ptr);
}

static void	ft_nm(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_MAGIC)
		ft_putendl("Don't wanna !");
}

static void	launch(char *path)
{
	struct stat		buff;
	char			*ptr;
	int				fd;

	if ((fd = open(path, O_RDONLY)) >= 0)
	{
		if (fstat(fd, &buff) >= 0)
		{
			if ((ptr = mmap(0, buff.st_size, PROT_READ,
				MAP_PRIVATE, fd, 0)) != MAP_FAILED)
			{
				ft_nm(ptr);
				if (munmap(ptr, buff.st_size) < 0)
					ft_putendl("Error munmap");
			}
			else
				ft_putendl("Error mmap");
		}
		else
			ft_putendl("Error fstats");
	}
	else
		ft_putendl("Error open");
}

int			main(int ac, char **av)
{
	int		i;

	if (ac >= 2)
	{
		i = 1;
		while (av[i])
		{
			if (ac > 2)
			{
				if (i < ac)
					write(1, "\n", 1);
				ft_putstr(av[i]);
				write(1, ":\n", 2);
			}
			launch(av[i]);
			i++;
		}
	}
	else
		launch("a.out");
	return (0);
}
