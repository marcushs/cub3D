# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:10:24 by hleung            #+#    #+#              #
#    Updated: 2023/10/12 20:44:25 by tduprez          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

NAME		=	cub3D
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
NO_PRI_DIR	=	--no-print-directory
LIBS		=	./minilibx-linux/libmlx_Linux.a ./libft/libft.a
LIBFLAGS	=	-L minilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -L libft -lft
HEADERS		=	includes
DIR_SRCS	=	srcs/
LIST_SRCS	=	main.c parse_config.c parse_utils.c parse_elements.c free.c init.c check_map.c render.c get_structs_address.c event.c move.c move_direction.c move_hitbox.c trim_spaces.c
SRCS		=	${addprefix ${DIR_SRCS}, ${LIST_SRCS}}
DIR_OBJS	=	.objs/
LIST_OBJS	=	${LIST_SRCS:.c=.o}
OBJS		=	${addprefix ${DIR_OBJS}, ${LIST_OBJS}}
RM			=	rm -rf

${DIR_OBJS}%.o:	${DIR_SRCS}%.c ${HEADERS}/cub3D.h
				@${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}
				
all:		${NAME}

${NAME}:	${DIR_OBJS} ${OBJS} ${LIBS} ${HEADERS}/cub3D.h
			@echo "${GREEN}Compiled source files!${NC}"
			${CC} ${CFLAGS} ${OBJS} ${LIBFLAGS} -o ${NAME}
			@echo "${GREEN}Cub3D is ready!${NC}"

${DIR_OBJS}:
			@mkdir -p ${DIR_OBJS}

${LIBS}:	force
			@${MAKE} ${NO_PRI_DIR} -sC ./libft
			@${MAKE} ${NO_PRI_DIR} -sC ./minilibx-linux

clean:		
			@${RM} ${DIR_OBJS}
			@${MAKE} ${NO_PRI_DIR} clean -sC ./libft
			@${MAKE} ${NO_PRI_DIR} clean -sC ./minilibx-linux
			@echo "${YELLOW}Object files and libraries cleared!${NC}"
			
fclean:		
			@${MAKE} ${NO_PRI_DIR} clean
			@${RM} ${NAME} 
			@${MAKE} fclean -sC ./libft
			@echo "${YELLOW}Executable cleared!${NC}"
			
re:			fclean 
			@$(MAKE) ${NO_PRI_DIR} all

.PHONY:		all clean fclean re .c.o force
