# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/17 23:39:56 by hlesny            #+#    #+#              #
#    Updated: 2023/12/17 23:41:43 by hlesny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = miniRT_bonus

CC = cc
CFLAGS = -MMD -g3 -I/opt/X11/include -I/opt/Xext/include -I$(INCLUDES_DIR) -Wall -Wextra -Werror

FILES = \
		camera/init_viewpoint \
		camera/set_aspect_ratio \
		create_elem/cr_camera \
		create_elem/cr_cylindre \
		create_elem/cr_light \
		create_elem/cr_mood_light \
		create_elem/cr_plan \
		create_elem/cr_sphere \
		create_elem/cr_cone \
		create_elem/material \
		create_elem/utils \
		exit \
		garbage_collector/ft_lstnew \
		garbage_collector/ft_lstadd_front \
		garbage_collector/ft_lstsize \
		garbage_collector/ft_lstlast \
		garbage_collector/ft_lstadd_back \
		garbage_collector/ft_lstdelone \
		garbage_collector/ft_lstclear \
		garbage_collector/ft_lstiter \
		garbage_collector/ft_vlstnew_with_mat \
		intersection/i_sphere \
		intersection/set_object_material \
		intersection/i_plan \
		intersection/i_cylindre \
		intersection/i_cylindre_caps \
		intersection/i_cone \
		intersection/i_circle \
		intersection/get_inter \
		intersection/solving_utils \
		intersection/solving_utils2 \
		maths_utils/intervals \
		maths_utils/distances/distance_point_line \
		maths_utils/distances/distance_two_lines \
		maths_utils/distances/distance_two_points \
		mlx_gestion/arrow_press \
		mlx_gestion/close \
		mlx_gestion/get_elem_vec \
		mlx_gestion/hooks \
		mlx_gestion/launch \
		mlx_gestion/mouse_hooks \
		mlx_gestion/print_usage \
		mlx_gestion/redraw \
		mlx_gestion/utils \
		utils/construct_map \
		utils/change_base \
		utils/fov \
		utils/ft_strcheck \
		utils/normaps_getter \
		utils/modulo \
		utils/point3d \
		utils/point3d2 \
		utils/ratio \
		utils/rgb \
		utils/set_checkers \
		utils/vec3d \
		utils_vec_et_droite/norm \
		utils_vec_et_droite/prod_scalaire \
		utils_vec_et_droite/prod_vec \
		utils_vec_et_droite/vec_operations \
		threads \
		main \
		parse \
		parse_utils \
		render/normals \
		render/point_sampling \
		render/cast_rays \
		render/shader/diffuse_reflection \
		render/shader/phong_model \
		render/shader/specular_reflection \
		render/shader/utils \
		render/shader/color \
		render/textures/checkers \
		render/textures/normals \
		render/textures/mapping/mapping \
		render/textures/mapping/sphere \
		render/textures/mapping/rotation_utils \
		render/textures/mapping/utils \
# Resolving


SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}

DEP_OBJS = $(OBJS:.o=.d)

LIBS_FOLDER = ../libs

LIBSR_DIR = libft
LIBSR = $(LIBS_FOLDER)/$(LIBSR_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(LIBS_FOLDER)/$(MLX_DIR)/libmlx_Linux.a
MLXFLAGS = -lX11 -lXext -lm

LIBMATRICE_DIR = libmatrices
LIBMATRICE = $(LIBS_FOLDER)/$(LIBMATRICE_DIR)/libmatrice.a

LIBS = $(MLX) $(LIBSR) $(LIBMATRICE)

INCLUDES_DIR = ./inc/

all: $(NAME)


$(NAME): $(LIBS) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(MLXFLAGS) -g -o $@

${OBJS_DIR}/%.o : ${SRCS_DIR}/%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/camera
	@mkdir -p $(OBJS_DIR)/create_elem
	@mkdir -p $(OBJS_DIR)/render
	@mkdir -p $(OBJS_DIR)/garbage_collector
	@mkdir -p $(OBJS_DIR)/intersection
	@mkdir -p $(OBJS_DIR)/mlx_gestion
	@mkdir -p $(OBJS_DIR)/maths_utils
	@mkdir -p $(OBJS_DIR)/maths_utils/distances
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/utils_vec_et_droite
	@mkdir -p $(OBJS_DIR)/render/shader
	@mkdir -p $(OBJS_DIR)/render/textures
	@mkdir -p $(OBJS_DIR)/render/textures/mapping
	$(CC) $(CFLAGS) -o $@ -c $< 

-include $(DEP_OBJS)

clean: cleanlibs
	rm -rf $(OBJS_DIR)

fclean: clean fcleanlibs 
	rm -f $(NAME)

re: fclean all

$(LIBS):
	make -C $(LIBS_FOLDER)/$(MLX_DIR)
	make -C $(LIBS_FOLDER)/$(LIBSR_DIR)
	make -C $(LIBS_FOLDER)/$(LIBMATRICE_DIR)

cleanlibs:
	make clean -C $(LIBS_FOLDER)/$(LIBSR_DIR)
	make clean -C $(LIBS_FOLDER)/$(LIBMATRICE_DIR)
	make clean -C $(LIBS_FOLDER)/$(MLX_DIR)

fcleanlibs:
	make fclean -C $(LIBS_FOLDER)/$(LIBSR_DIR)
	make fclean -C $(LIBS_FOLDER)/$(LIBMATRICE_DIR)

.PHONY: all clean fclean re makelib cleanlib
