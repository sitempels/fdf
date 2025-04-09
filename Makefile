# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stempels <stempels@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/04/09 10:13:42 by stempels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
#MAKEFLAGS += --silent
#
NAME = fdf 
TYPE = EXEC
#----------------------------COMPILER------------------------------------------#
CC = cc 
CCFLAGS = -Wall -Werror -Wextra -g
CPPFLAGS = $(INC_FLAG)
#
#----------------------------LINKER--------------------------------------------#
#----------------------------DEBUG---------------------------------------------#
#----------------------------MAIN----------------------------------------------#
#----------------------------SRC-----------------------------------------------#
SRC_DIR = src
SRC = $(addprefix src/, $(addsuffix .c, main_fdf fdf point_handler fdf_utils)) 
#
#----------------------------OBJ-----------------------------------------------#
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
#
#----------------------------LIB-----------------------------------------------#
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
#
MLBX_DIR = mlbx
MLBX = $(MLBX_DIR)/libmlx_Linux.a
#
INC_FLAG += $(addprefix -I, $(LIBFT_DIR)/$(INC_DIR) $(MLBX_DIR))
LINK_FLAG += $(addprefix -L, $(LIBFT_DIR) $(MLBX_DIR)) $(addprefix -l, ft mlx_Linux)
#
#----------------------------HEADER--------------------------------------------#
INC_DIR = include
INC_FLAG += -I$(INC_DIR)
#
#----------------------------RULES---------------------------------------------#
all: $(NAME)
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -O3 -c $< -o $@
#
lib:	$(LIBFT) 
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
#
$(MLBX):
	@$(MAKE) -C $(MLBX_DIR)
#
$(NAME): $(OBJ) $(LIBFT) $(MLBX)
	$(CC) $(OBJ) $(LINK_FLAG) -lX11 -lXext -lm -lz -o $@
	@echo "$(NAME) $(GREEN)created !$(NC)"
#
clean:	libclean
	rm -rf $(OBJ_DIR)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
libclean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(LIBFT)
	$(MAKE) clean -C $(MLBX_DIR)
	rm -rf $(MLBX)
#
#
fclean: clean
	rm -rf $(NAME)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
re: fclean all
#
.PHONY: all clean libclean fclean re design
#----------------------------TEXT----------------------------------------------#
GREEN=\033[0;32m
NC=\033[0m
#
#----------------------------MISC----------------------------------------------#
#
