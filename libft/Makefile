# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 15:09:16 by rmakinen          #+#    #+#              #
#    Updated: 2023/10/19 16:37:18 by rmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
LIB_DIR = includes
SRC_DIR = sources/
OBJ_DIR = objects/
INCLUDES = $(addprefix ./includes/, ft_printf.h libft.h get_next_line.h)
FLAGS = -c
CC = cc
AR = ar rcs

CONVERT_DIR = convert/
CONVERT = ft_tolower ft_toupper ft_itoa ft_atoi ft_swap

CHECK_DIR = check/
CHECK =ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint

MEM_DIR = mem/
MEM = ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_bzero

PUT_DIR = put/
PUT = ft_putchar ft_putstr ft_putnbr ft_putchar_fd ft_putstr_fd ft_putnbr_fd ft_putendl_fd

STR_DIR = string/
STRING = ft_strmapi ft_striteri ft_strchr ft_strlen ft_strlcpy ft_strncmp \
		ft_strrchr ft_substr ft_strjoin ft_strtrim ft_strchr ft_split \
		ft_strnstr ft_strlcat ft_strdup ft_strcmp ft_strlen_int \

PRINT_DIR = print/
PRINT = ft_printf print_percentage print_pointer print_putchar print_puthexhi \
		print_puthexlow print_putnum print_putstring print_unsigned

GNL_DIR = gnl/
GNL = get_next_line get_next_line_utils

SRC_FILE+=$(addprefix $(CONVERT_DIR), $(CONVERT))
SRC_FILE+=$(addprefix $(CHECK_DIR), $(CHECK))
SRC_FILE+=$(addprefix $(MEM_DIR), $(MEM))
SRC_FILE+=$(addprefix $(PUT_DIR), $(PUT))
SRC_FILE+=$(addprefix $(STR_DIR), $(STRING))
SRC_FILE+=$(addprefix $(PRINT_DIR), $(PRINT))
SRC_FILE+=$(addprefix $(GNL_DIR), $(GNL))

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILE)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILE)))

OBJECTS = exists

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJECTS)
	@$(CC) $(FLAGS) -I$(LIB_DIR) -c $< -o $@

$(OBJECTS):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(CONVERT_DIR)
	@mkdir -p $(OBJ_DIR)$(CHECK_DIR)
	@mkdir -p $(OBJ_DIR)$(MEM_DIR)
	@mkdir -p $(OBJ_DIR)$(PUT_DIR)
	@mkdir -p $(OBJ_DIR)$(STR_DIR)
	@mkdir -p $(OBJ_DIR)$(PRINT_DIR)
	@mkdir -p $(OBJ_DIR)$(GNL_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJECTS)
	@cc $(FLAGS) -I$(LIB_DIR) -c $< -o $@

what:
	echo $(OBJECTS)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
