/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/04 16:22:17 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/04 16:22:18 by pivanovi         ###   ########.fr       */
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
#include "otool.h"

static char	*rev_by_pair(char *str)
{
	char	tmp;
	int		i;

	i = 0;
	while (str[i + 1])
	{
		tmp = str[i];
		str[i] = str[i + 1];
		str[i + 1] = tmp;
		i += 2;
	}
	return (str);
}

void		handle_64(char *ptr)
{
	t_segment			*seg_c;
	struct section_64	*sec;
	unsigned int		i;
	uint64_t			*addr;

	seg_c = get_segment(ptr);
	sec = (void *)seg_c + sizeof(t_segment);
	while (ft_strcmp(sec->sectname, "__text"))
		sec = (void *)sec + sizeof(struct section_64);
	i = 0;
	while (i < sec->size)
	{
		ft_putstr(b_to_h(d_to_b(sec->addr + i), "0123456789abcdef"));
		ft_putstr(" ");
		addr = (void *)ptr + sec->offset + i;
		special_print(str_rev(rev_by_pair(b_to_h(d_to_b(*addr),
			"0123456789abcdef"))), 0, sec->size - i);
		special_print(str_rev(rev_by_pair(b_to_h(d_to_b(*(addr + 1)),
			"0123456789abcdef"))), 1, sec->size - i - 8);
		i += 16;
	}
}

static void	ft_otool(char *ptr)
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
				ft_otool(ptr);
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
			ft_putstr(av[i]);
			write(1, ":\n", 2);
			write(1, "(__TEXT,__text) section\n", 24);
			launch(av[i]);
			i++;
		}
	}
	else
		ft_putendl("At least one file must be specified");
	return (0);
}
