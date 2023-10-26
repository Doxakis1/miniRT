# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 13:30:50 by rmakinen          #+#    #+#              #
#    Updated: 2023/10/26 10:10:10 by mkaratzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
SRC = main.c \
		create_output_file.c \
		scene.c \
		vectors/vector_math.c \
		vectors/vector_math2.c \
		shader/normals.c \
		shader/light.c \
		shader/shadows.c \
		parser/ft_atox.c \
		parser/ft_print_error.c \
		parser/get_ambient_light.c \
		parser/get_new_object.c \
		parser/get_camera.c \
		parser/get_light_source.c \
		parser/get_object_identifier.c \
		parser/parser_utils.c \
		parser/parser_utils2.c \
		parser/parser.c \
		shader/colors.c \
		shader/color_math.c \
		shader/color_math2.c \
		shader/object_colors.c \
		ray_functions/ray_hit.c \
		ray_functions/object_intersection.c \
		ray_functions/cylinder_utils1.c \
		ray_functions/cylinder_utils2.c \
		ray_functions/cylinder_utils3.c \
		check_camera_pos.c \

OBJ = main.o \
		create_output_file.o \
		scene.o \
		vector_math.o \
		vector_math2.o \
		normals.o \
		light.o \
		shadows.o \
		ft_atox.o \
		ft_print_error.o \
		get_camera.o \
		get_light_source.o \
		get_ambient_light.o \
		get_new_object.o \
		get_object_identifier.o \
		parser_utils.o \
		parser_utils2.o \
		parser.o \
		ray_hit.o \
		colors.o \
		color_math.o \
		color_math2.o \
		object_colors.o \
		object_intersection.o \
		cylinder_utils1.o \
		cylinder_utils2.o \
		cylinder_utils3.o \
		check_camera_pos.o \

INCL = includes/minirt.h \
		includes/parser.h \
		includes/vectors.h \

LIB_DIR = includes

#DEBUG = -g -fsanitize=address,undefined

FLAGS = -Wall -Wextra -Werror -O2

SPECULAR = -D SPECULAR=1

all: $(NAME)

$(NAME): $(SRC) $(INCL)
	@cd libft && $(MAKE)
	@cc $(FLAGS) -c $(SRC)
	#@cc $(FLAGS) $(OBJ) -I$(LIB_DIR) libft/libft.a -L /usr/local/include -o $(NAME)
	@cc $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)

specular: $(SRC) $(INCL)
	@cd libft && $(MAKE)
	@cc $(FLAGS) $(SPECULAR) -c $(SRC)
	#@cc $(FLAGS) $(OBJ) -I$(LIB_DIR) libft/libft.a -L /usr/local/include -o $(NAME)
	@cc $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)

clean:
	@cd libft && make clean
	@rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re