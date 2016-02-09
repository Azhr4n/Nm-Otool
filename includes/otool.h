/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/04 16:18:34 by pivanovi          #+#    #+#             */
/*   Updated: 2014/10/04 16:18:34 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

typedef struct segment_command_64	t_segment;

void		special_print(char *str, int option, int j);

t_segment	*get_segment(void *ptr);

#endif
