# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srapin <srapin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 12:01:36 by Helene            #+#    #+#              #
#    Updated: 2023/11/08 18:37:39 by srapin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmatrice.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

FILES=	 \
	create \
	del \
	print_mat \
	basic_operations \

SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES))) 

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}


${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

# LIBFT_DIR = mylibft/
# LIBFT_NAME = lib.a
# LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

$(NAME): $(OBJS) $(LIBFT)
	${AR} $@ $(OBJS)
# cp ${LIBFT} $@


# $(LIBFT) :
# 		make -C $(LIBFT_DIR)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re
