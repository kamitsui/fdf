# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/11 20:51:49 by kamitsui          #+#    #+#              #
#    Updated: 2023/06/20 21:07:35 by kamitsui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = ../include
DEP_DIR = .dep

# Source files
SRCS = \
	   ft_bzero.c \
	   ft_isdigit.c \
	   ft_isxdigit.c \
	   ft_itoa.c \
	   ft_itoa_binary.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_split.c \
	   ft_strchr.c \
	   ft_strdup.c \
	   ft_strjoin.c \
	   ft_strjoin_free.c \
	   ft_strlcat.c \
	   ft_strlcpy.c \
	   ft_strlen.c \
	   ft_strncat.c \
	   ft_strncmp.c \
	   ft_strndup.c \
	   ft_strnequ.c \
	   ft_strnew.c \
	   ft_strnlen.c \
	   ft_strtok.c \
	   \
	   get_next_line.c

# Object files and dependency files
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
DEPS = $(addprefix $(DEP_DIR)/, $(SRCS:%.c=%.d))

# Vpath
vpath $(SRCS) $(SRC_DIR)

# Library name
LIB = libft.a

# Compiler
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -MMD -MP -MF $(@:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)
INC = -I$(INC_DIR)

# Rules for building object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP_DIR)/%.d
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) $(INC) -c $< -o $@

$(DEP_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(DEP_DIR)

# Default target
all: $(LIB)

# Library target
$(LIB): $(OBJS)
	ar rcs $@ $^

$(OBJS): $(DEPS)

# Clean target
clean:
	rm -fr $(OBJ_DIR) $(DEP_DIR)

# Clean and remove library target
fclean: clean
	rm -f $(LIB)

# Rebould target
re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
