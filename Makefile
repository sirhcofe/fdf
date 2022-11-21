# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 12:03:33 by chenlee           #+#    #+#              #
#    Updated: 2022/11/21 21:30:18 by chenlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Linux)
	LIBX = minilibx/minilibx_linux/
endif
ifeq ($(UNAME), Darwin)
	LIBX = minilibx/minilibx_macos/
endif

NAME		=	libfdf.a
FRAMEWORK	=	-framework OpenGL -framework AppKit
FLAGS		=	-Wall -Werror -Wextra
OBJS_DIR	=	objects/
OBJS		=	$(addprefix $(OBJS_DIR), $(notdir $(SRC:.c=.o)))

SRC			=	

SRC_DIR		=	fdf				\
				includes		\
				$(LIBX)
vpath %.c $(SRC_DIR)

all:			$(NAME) fdf

$(NAME):		$(OBJS)
			@make -C $(LIBX) all
			@make -C libft/ all
# @gcc $(FLAGS) -I$(LIBX) $(SRC) -o fdf $(FRAMEWORK)
# @ar rc $(NAME) $(OBJS)

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(OBJS_DIR)
			@echo "Compiling: $<"
			@gcc $(CFLAGS) -I$(LIBX) -c $< -o $@

fdf:		main.c
			@gcc $(CFLAGS) main.c -L$(LIBX) -lmlx -Llibft -lft -o fdf $(FRAMEWORK)

clean:
			@make -C libft/ clean
			@rm -rf objects
			@make -C $(LIBX) clean
			@echo "Done!"

fclean:			clean
			@make -C libft/ fclean
			@rm -rf $(NAME) fdf
			@echo "Done!"

re:			fclean all
