# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/03 15:30:43 by pivanovi          #+#    #+#              #
#    Updated: 2014/04/21 19:45:22 by pivanovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME1 = ft_nm
NAME2 = ft_otool

SRC1 =		tools/tools_str.c				\
			tools/convert.c					\
			tools/tools.c					\
			src_nm/struct.c					\
			src_nm/get.c					\
			src_nm/nm.c

SRC2 =		tools/tools_str.c				\
			tools/convert.c					\
			tools/tools.c					\
			src_otool/get.c					\
			src_otool/otool.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

CFLAGS += -I./includes

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o $@

$(NAME2): $(OBJ2)
	$(CC) $(CFLAGS) $(OBJ2) -o $@

clean:
	/bin/rm -f $(OBJ1) && /bin/rm -f $(OBJ2)

fclean: clean
	/bin/rm -f $(NAME1) && /bin/rm -f $(NAME2)

re: fclean all
