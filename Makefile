# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 11:25:47 by asangerm          #+#    #+#              #
#    Updated: 2024/03/18 18:46:45 by nfradet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME	=	minishell
INC		=	-I./includes

# Flags
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

# Directories
SRC_DIR	=	src/
OBJ_DIR	=	obj/
LIB_DIR	=	libft/

# .c and .o files
SRC		=	$(wildcard $(SRC_DIR)*.c)
OBJ		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# .a files
LIBFT	=	$(LIB_DIR)libft.a

# The main rule
all				:	$(NAME)

# The name rule
$(NAME)			:	$(OBJ) $(LIBFT)
	@echo "\033[0;33mCompiling the whole project -> ⏳\033[0m"
	@$(CC) $(OBJ) $(LIBFT) -o $@
	@echo "\033[0;32mProject successfuly compiled -> ✅\033[0m\n"

# The libft rule
$(LIBFT)		:	$(LIB_DIR)
	@echo "\033[0;33mCompiling my libft -> ⏳\033[0m"
	@make all -sC $<
	@echo "\033[0;32mLibft successfuly compiled -> ✅\033[0m\n"

# Compile .c to .o files
$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "\033[0;33mCompiling project src -> ⏳\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "\033[0;32mSrc's project successfuly compiled -> ✅\033[0m\n"

# Create the obj directory
$(OBJ_DIR)		:
	@mkdir -p $@

# Clean, fclean and re rules
clean			:
	@echo "\033[0;31mCleaning obj files -> 🗑️\033[0m"
	@rm -rf $(OBJ_DIR)
	@make clean -sC $(LIB_DIR)
	@echo "\033[0;32mDone -> ✅\033[0m\n"

fclean			:	clean
	@echo "\033[0;31mCleaning program -> 🗑️\033[0m"
	@rm -rf $(NAME)
	@make fclean -sC $(LIB_DIR)
	@echo "\033[0;32mDone -> ✅\033[0m\n"
re				:	fclean all

