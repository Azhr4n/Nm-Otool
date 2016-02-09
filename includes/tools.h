/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/02 16:53:10 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/02 16:53:10 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>

int			ft_strlen(char *str);
int			ft_strcmp(char *s1, char *s2);

int			*d_to_b(uint64_t n);

void		ft_putnbr(int n);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_putendl(char *str);

char		*str_rev(char *str);
char		*b_to_h(int *tab, char *hexa);

#endif
