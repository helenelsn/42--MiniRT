# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srapin <srapin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 22:16:42 by srapin            #+#    #+#              #
#    Updated: 2023/10/18 23:47:26 by srapin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

FILES = \
		create_elem/cr_mood_light\
		garbage_collector/ft_lstnew\
		garbage_collector/ft_lstadd_front\
		garbage_collector/ft_lstsize\
		garbage_collector/ft_lstlast\
		garbage_collector/ft_lstadd_back\
		garbage_collector/ft_lstdelone\
		garbage_collector/ft_lstclear\
		garbage_collector/ft_lstiter \
		utils/atof \
		utils/ft_strcheck \
		main\
		parse\
		
	
SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES))) 

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}
# OBJS = ${patsubst ${SRCS_DIR}/%.c, %.o, ${SRCS}}

LIBS_FOLDER = libs

LIBSR_DIR = libft
LIBSR = $(LIBS_FOLDER)/$(LIBSR_DIR)/libft.a

MLX_DIR = minilibx-linux/
MLX = ./$(LIBS_FOLDER)/$(MLX_DIR)/libmlx_Linux.a

LIBS = $(MLX) $(LIBSR)

INCLUDES_DIR = includes
INCLUDES_FILES = fractol.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -lm -lXext -lX11 -g -o $@

bonus: $(NAME)

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c 
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/create_elem
	@mkdir -p $(OBJS_DIR)/garbage_collector
	@mkdir -p $(OBJS_DIR)/utils
	$(CC) $(CFLAGS) -o $@ -c $<

clean: cleanlibs
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all

$(LIBS):
	make -C $(LIBS_FOLDER)/$(MLX_DIR)
	make -C $(LIBS_FOLDER)/$(LIBSR_DIR)

cleanlibs:
	make fclean -C $(LIBS_FOLDER)/$(LIBSR_DIR)
	make clean -C $(LIBS_FOLDER)/$(MLX_DIR)

.PHONY: all clean fclean re makelib cleanlib
