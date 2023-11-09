# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Helene <Helene@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 22:16:42 by srapin            #+#    #+#              #
#    Updated: 2023/11/09 15:09:48 by Helene           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I/opt/X11/include -I/opt/Xext/include

FILES = \
		create_elem/cr_camera\
		create_elem/cr_cylindre\
		create_elem/cr_light\
		create_elem/cr_mood_light\
		create_elem/cr_plan\
		create_elem/cr_sphere\
		garbage_collector/ft_lstnew\
		garbage_collector/ft_lstadd_front\
		garbage_collector/ft_lstsize\
		garbage_collector/ft_lstlast\
		garbage_collector/ft_lstadd_back\
		garbage_collector/ft_lstdelone\
		garbage_collector/ft_lstclear\
		garbage_collector/ft_lstiter \
		intersection/i_sphere \
		intersection/i_plan \
		utils/atof \
		utils/fov \
		utils/ft_strcheck \
		utils/point3d \
		utils/ratio \
		utils/rgb \
		utils/vec3d \
		utils_vec_et_droite/norm \
		utils_vec_et_droite/prod_scalaire \
		utils_vec_et_droite/prod_vec \
		main\
		parse\
		bsp/create_bsp \
		bsp/bounding_volumes \
		bsp/get_splitting_plane \
		bsp/search \
		# trace_rays/trace_ray \
		# trace_rays/convert \ 

		
	
SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES))) 

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}
# OBJS = ${patsubst ${SRCS_DIR}/%.c, %.o, ${SRCS}}

LIBS_FOLDER = libs

LIBSR_DIR = libft
LIBSR = $(LIBS_FOLDER)/$(LIBSR_DIR)/libft.a


MLX_DIR = minilibx-linux
MLX = $(LIBS_FOLDER)/$(MLX_DIR)/libmlx_Linux.a
MLXFLAGS = -lX11 -lXext -lm

# LIBMATRICE_DIR = libmatrices
# LIBMATRICE = $(LIBS_FOLDER)/$(LIBMATRICE_DIR)/libmatrice.a

LIBS = $(MLX) $(LIBSR) $(LIBMATRICE)

INCLUDES_DIR = includes
INCLUDES_FILES = fractol.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(MLXFLAGS) -g -o $@

bonus: $(NAME)

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c 
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/bsp
	@mkdir -p $(OBJS_DIR)/create_elem
	@mkdir -p $(OBJS_DIR)/trace_rays
	@mkdir -p $(OBJS_DIR)/garbage_collector
	@mkdir -p $(OBJS_DIR)/intersection
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/utils_vec_et_droite
	$(CC) $(CFLAGS) -o $@ -c $<

clean: cleanlibs
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all

$(LIBS):
	make -C $(LIBS_FOLDER)/$(MLX_DIR)
	make -C $(LIBS_FOLDER)/$(LIBSR_DIR)
# make -C $(LIBS_FOLDER)/$(LIBMATRICE_DIR)

cleanlibs:
	make fclean -C $(LIBS_FOLDER)/$(LIBSR_DIR)
	make clean -C $(LIBS_FOLDER)/$(MLX_DIR)

.PHONY: all clean fclean re makelib cleanlib
