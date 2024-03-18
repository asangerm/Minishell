# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 16:40:14 by asangerm          #+#    #+#              #
#    Updated: 2023/10/24 15:45:20 by asangerm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME	=	libft.a

# Flags
CC		=	gcc
CFLAGS	=	-Werror -Wextra -Wall
AR		=	ar rcs

# Directories
SRC_DIR	=	src
OBJ_DIR	=	obj
LIB_DIR	=	libft

# .c and .o files
SRC		=	$(wildcard $(SRC_DIR)/*.c)
OBJ		=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# The main rule
all		:	$(NAME)

# Compile the lib
$(NAME)	:	$(OBJ)
	@$(AR) $@ $(OBJ)

# Compile .c to .o files
$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Create the obj directory
$(OBJ_DIR)	:
	@mkdir -p $@

# Clean, fclean and re rules
clean	:
	@rm -rf $(OBJ_DIR)
fclean	:	clean
	@rm -rf $(NAME)
re		:	fclean all