# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/13 13:59:50 by kamitsui          #+#    #+#              #
#    Updated: 2023/07/13 16:04:05 by kamitsui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target name
NAME = fdf

# Libraries
MLX_PATH = /Users/kamitsui/lib
MLX_DYLB = $(MLX_PATH)/libmlx.dylib
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIB_PRINTF_DIR = ft_printf
LIB_PRINTF = $(PRINTF_DIR)/libftprintf.a

# Include Header
INC_DIR = include

# Sources
SRC_DIR = src
SRCS = fdf.c

# vpath for serching source files in multiple directories
vpath %.c $(SRC_DIR)

# Objects
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Dependency files
DEP_DIR = .dep
DEPS = $(addprefix $(DEP_DIR)/, $(SRCS:.c=.d))

# Compile
CC = clang
CF = -Wall -Wextra -Werror
INC_CF = -I$(INC_DIR)
DEP_CF = -MMD -MP -MF $(@:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)
MLX_CF = -lmlx
FRAMEWORK_CF = -framework OpenGL -framework AppKit

# Rules for building object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)
	$(CC) $(CF) $(INC_CF) $(DEP_CF) -c $< -o $@

# Rules for building dependency files
$(DEP_DIR)/%.d: %.c
	@mkdir -p $(DEP_DIR)

# Default target
all: $(NAME)

# Target
$(NAME): $(LIB_PRINTF) $(MLX_DYLB) $(DEPS) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIB_PRINTF) -L $(MLX_PATH) $(MLX_CF)

# Library target
$(LIB_PRINTF): $(LIBFT)
	$(MAKE) -C $(LIB_PRINTF_DIR)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


#$(MLX_DYLB):
#	@printf "Please install libmlx.dylb"

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

# Clean and remove target
fclean: clean
	rm -f $(NAME)

# Rebuild target
re: fclean all

# Enable dependency file
-include $(DEPS)

.PHONY: all bonus clean fclean re
