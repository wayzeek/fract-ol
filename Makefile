# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcart <vcart@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/07 12:26:23 by vcart             #+#    #+#              #
#    Updated: 2022/12/19 13:42:20 by vcart            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./srcs/mandelbrot.c ./srcs/main.c ./srcs/colors.c ./srcs/hooks.c ./srcs/utils.c

OBJS = ${SRCS:.c=.o}

HEADERS = ./fract_ol.h

NAME = fractol

CFLAGS = -Wall -Wextra -Werror 

LINK = -framework OpenGL -framework AppKit

${NAME}:	${OBJS} ./mlx ${HEADERS} Makefile
			make -C ./mlx
			$(CC) ${CFLAGS} ${OBJS} ${LINK} ./mlx/libmlx.a -o ${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean
		$(MAKE) all

.PHONY:	all clean fclean re 