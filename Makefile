# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcart <vcart@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/07 12:26:23 by vcart             #+#    #+#              #
#    Updated: 2022/12/07 12:52:41 by vcart            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./srcs/julia.c

OBJS = ${SRCS:.c=.o}

HEADERS = ./fract_ol.h

NAME = fractol

CFLAGS = -framework OpenGL -framework AppKit -Wall -Wextra -Werror

%.o: %.c ${HEADERS} Makefile
	${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}

${NAME}:	${OBJS} 
			$(AR) rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean
		$(MAKE) all

.PHONY:	all clean fclean re 