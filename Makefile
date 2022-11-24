# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 12:03:33 by chenlee           #+#    #+#              #
#    Updated: 2022/11/24 15:31:53 by chenlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Linux)
	LIBX = minilibx/minilibx_linux/
	COMPILE = -L$(LIBX) -lmlx_Linux -L/usr/lib -I$(LIBX) -lXext -lX11 -lm -lz
endif
ifeq ($(UNAME), Darwin)
	LIBX = minilibx/minilibx_macos/
	COMPILE = -L$(LIBX) -lmlx -framework OpenGL -framework AppKit
endif

NAME		=	libfdf.a
FLAGS		=	-Wall -Werror -Wextra
OBJS_DIR	=	objects/
OBJS		=	$(addprefix $(OBJS_DIR), $(notdir $(SRC:.c=.o)))

SRC			=	drawaaline.c			\
				drawaaline_utils.c

SRC_DIR		=	fildefer/draw-aa-line	\
				includes				\
				$(LIBX)
vpath %.c $(SRC_DIR)

INCLUDES	=	-Ilibft -Iincludes

all:			$(NAME) fdf

$(NAME):		$(OBJS)
			@make -C $(LIBX) all
			@make -C libft/ all
# @gcc $(FLAGS) -I$(LIBX) $(SRC) -o fdf $(FRAMEWORK)
			@ar rc $(NAME) $(OBJS)

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(OBJS_DIR)
			@echo "Compiling: $<"
			gcc $(FLAGS) -I$(LIBX) $(INCLUDES) -c $< -o $@

fdf:		main.c
			gcc $(FLAGS) main.c -L. -lfdf $(INCLUDES) $(COMPILE) -o fdf

clean:
			@rm -rf objects
			@make -C $(LIBX) clean
			@echo "Done!"

fclean:		clean
			@rm -rf $(NAME) fdf
			@echo "Done!"

re:			fclean all
