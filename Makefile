
NAME = mimirt

CC = cc
CFLAGS = -MMD -g3 -I/opt/X11/include -I/opt/Xext/include -I$(INCLUDES_DIR) #-Wall -Wextra -Werror -I

FILES = \
		bsp/bounding_volumes \
		bsp/create_bsp \
		bsp/get_splitting_plane \
		bsp/recursive_ray_traversal \
		create_elem/cr_camera \
		create_elem/cr_cylindre \
		create_elem/cr_light \
		create_elem/cr_mood_light \
		create_elem/cr_plan \
		create_elem/cr_sphere \
		dist/dist_droite \
		dist/dist_points \
		dist/dist_point_droite \
		garbage_collector/ft_lstnew \
		garbage_collector/ft_lstadd_front \
		garbage_collector/ft_lstsize \
		garbage_collector/ft_lstlast \
		garbage_collector/ft_lstadd_back \
		garbage_collector/ft_lstdelone \
		garbage_collector/ft_lstclear \
		garbage_collector/ft_lstiter \
		garbage_collector/ft_vlst_del_in_list \
		intersection/i_sphere \
		intersection/i_plan \
		intersection/i_cylindre \
		intersection/get_inter \
		intersection/solving_utils \
		mlx_gestion/close \
		mlx_gestion/hooks_resize \
		mlx_gestion/hooks \
		mlx_gestion/init \
		mlx_gestion/key_press \
		mlx_gestion/launch \
		mlx_gestion/utils \
		utils/atof \
		utils/change_base \
		utils/fov \
		utils/ft_strcheck \
		utils/modulo \
		utils/point3d \
		utils/ratio \
		utils/rgb \
		utils/set_specular \
		utils/set_reflective \
		utils/set_checkers \
		utils/vec3d \
		utils_vec_et_droite/norm \
		utils_vec_et_droite/prod_scalaire \
		utils_vec_et_droite/prod_vec \
		utils_vec_et_droite/vec_operations \
		main \
		parse \
		trace_rays/color \
		trace_rays/light \
		trace_rays/normals \
		trace_rays/point_sampling \
		trace_rays/screen_scene_utils \
		trace_rays/trace_ray \
		camera/init_viewpoint \
		trace_rays/intervals_utils \
		trace_rays/textures/mapping \
		trace_rays/textures/checkers 
# Resolving
		
	
SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES))) 

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}

#DEP_OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.d, ${SRCS}}
DEP_OBJS = $(OBJS:.o=.d)

LIBS_FOLDER = libs

LIBSR_DIR = libft
LIBSR = $(LIBS_FOLDER)/$(LIBSR_DIR)/libft.a


MLX_DIR = minilibx-linux
MLX = $(LIBS_FOLDER)/$(MLX_DIR)/libmlx_Linux.a
MLXFLAGS = -lX11 -lXext -lm

LIBMATRICE_DIR = libmatrices
LIBMATRICE = $(LIBS_FOLDER)/$(LIBMATRICE_DIR)/libmatrice.a

LIBS = $(MLX) $(LIBSR) $(LIBMATRICE)

INCLUDES_DIR = ./inc/
# INCLUDES_FILES = fractol.h # ???????????????????
# INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(MLXFLAGS) -g -o $@
#@echo "mimirt compiled"

${OBJS_DIR}/%.o : ${SRCS_DIR}/%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/bsp
	@mkdir -p $(OBJS_DIR)/camera
	@mkdir -p $(OBJS_DIR)/create_elem
	@mkdir -p $(OBJS_DIR)/dist
	@mkdir -p $(OBJS_DIR)/trace_rays
	@mkdir -p $(OBJS_DIR)/garbage_collector
	@mkdir -p $(OBJS_DIR)/intersection
	@mkdir -p $(OBJS_DIR)/mlx_gestion
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/utils_vec_et_droite
	@mkdir -p $(OBJS_DIR)/checkerboard
	@mkdir -p $(OBJS_DIR)/trace_rays/textures
	$(CC) $(CFLAGS) -o $@ -c $< 
#$(INCLUDES_DIR) 

-include $(DEP_OBJS)
#-include $(DEP_OBJS)/bsp
#-include $(DEP_OBJS)/create_elem
#-include $(DEP_OBJS)/dist
#-include $(DEP_OBJS)/trace_rays
#-include $(DEP_OBJS)/garbage_collector
#-include $(DEP_OBJS)/intersection
#-include $(DEP_OBJS)/mlx_gestion
#-include $(DEP_OBJS)/utils
#-include $(DEP_OBJS)/utils_vec_et_droite
@echo "=================================Dependencies: $(DEP_OBJS)"

clean: cleanlibs
	rm -r $(OBJS_DIR)

fclean: clean fcleanlibs 
	rm $(NAME)

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
