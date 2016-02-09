/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 16:50:56 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/02 16:50:56 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "tools.h"

int			ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void		ft_putendl(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void		ft_putnbr(int n)
{
	if (n < 0)
		ft_putchar('-');
	if (n / 10 != 0)
	{
		if (n < 0)
			ft_putnbr(-(n / 10));
		else
			ft_putnbr(n / 10);
	}
	n %= 10;
	if (n < 0)
		n = -n;
	ft_putchar('0' + n);
}
