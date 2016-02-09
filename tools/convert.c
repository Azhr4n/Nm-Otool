/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 16:55:26 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/02 16:55:27 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tools.h"
#include "nm.h"

int			*d_to_b(uint64_t n)
{
	int		*tab;
	int		i;

	if (!(tab = (int *)malloc(sizeof(int) * 64)))
		return (0);
	i = 0;
	while (i < 64)
	{
		tab[i] = n % 2;
		n /= 2;
		i++;
	}
	return (tab);
}

static void	set_var(int *val)
{
	val[2] = -1;
	val[3] = 0;
	val[1] = 1;
	val[0] = 0;
}

char		*b_to_h(int *tab, char *hexa)
{
	int			val[4];
	char		*str;

	if (!(str = (char *)malloc(sizeof(char) * 17)))
		return (0);
	str[16] = 0;
	set_var(val);
	while (++val[2] < 64)
	{
		val[0] += tab[val[2]] * val[1];
		val[1] *= 2;
		if (!((val[2] + 1) % 4))
		{
			str[val[3]] = hexa[val[0]];
			val[1] = 1;
			val[0] = 0;
			val[3]++;
		}
	}
	str = str_rev(str);
	free(tab);
	return (str);
}
