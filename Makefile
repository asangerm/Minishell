# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 11:25:47 by asangerm          #+#    #+#              #
#    Updated: 2024/06/06 04:21:09 by asangerm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME	=	minishell
INC		=	-I./includes

# Flags
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

# Directories
VPATH   =   src src/parsing src/env src/builtins src/free src/executor
OBJ_DIR	=	obj/
LIB_DIR	=	libft/

# .c and .o files
FREE	 =	free.c

EXECUTOR =	pipes.c			\
			pipes_utils.c	\
			files_handler.c	\
			exec_utils.c			\
			execution.c

ENV		 =	env.c			\
			env_utils_2.c	\
			utils.c

PARSING	 =  handlers_0.c	\
			extracters_0.c	\
			parsing_0.c  	\
			ft_newsplit.c	\
			parsing_1.c 	\
			utils_chain_0.c \
			utils_chain_1.c \
			utils_str_0.c

BUILTINS =  builtins.c		\
			ft_echo.c		\
			ft_cd.c			\
			ft_exit.c		\
			ft_export.c		\
			ft_unset.c		\
			export_utils.c

SRC		 =	$(PARSING)		\
			$(ENV)			\
			$(BUILTINS) 	\
			$(FREE) 		\
			$(EXECUTOR)		\
			main.c

OBJ		 =	$(SRC:%.c=$(OBJ_DIR)%.o)

# .a files
LIBFT	 =	$(LIB_DIR)libft.a

# The main rule
all				:	$(NAME)

# The name rule
$(NAME)			:	$(OBJ_DIR) $(OBJ) $(LIBFT)
	@echo "\033[0;33mCompiling the whole project -> ⏳\033[0m"
	@$(CC) $(OBJ) $(LIBFT) -o $@ -lreadline
	@echo "\033[0;32mProject successfuly compiled -> ✅\033[0m\n"

# The libft rule
$(LIBFT)		:	$(LIB_DIR)
	@echo "\033[0;33mCompiling my libft -> ⏳\033[0m"
	@make all -sC $<
	@echo "\033[0;32mLibft successfuly compiled -> ✅\033[0m\n"

# Compile .c to .o files
$(OBJ_DIR)%.o	:	%.c
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

