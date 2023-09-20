# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hleung <hleung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:10:24 by hleung            #+#    #+#              #
#    Updated: 2023/09/20 15:01:34 by hleung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LIBFTFLAGS	=	-L libft -lft
MLXFLAGS	=	-L mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
HEADERS		=	includes
DIR_SRCS	=	srcs/
LIST_SRCS	=	
SRCS		=	${addprefix ${DIR_SRCS}, ${LIST_SRCS}}
DIR_OBJS	=	.objs/
LIST_OBJS	=	${LIST_SRCS.c=.o}
OBJS		=	${addprefix ${DIR_OBJS}, ${LIST_OBJS}}
RM			=	rm -rf

${DIR_OBJS}%.o:	${DIR_SRCS}%.c ${HEADERS}/cub3D.h
				${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}
				
all:	${NAME}

${NAME}:	${SRCS} ${OBJS} ${HEADERS}/cub3D.h
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${DIR_OBJS}:
			@mkdir -p ${DIR_OBJS}

${LIB}:		force
			${MAKE} -sC ./libft
			${MAKE} -sC ./
