# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 01:48:56 by hlesny            #+#    #+#              #
#    Updated: 2023/12/18 01:48:58 by hlesny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NORMAL_DIR = ./mimi_rt
BONUS_DIR = ./mimi_rt_bonus

all:
	make -C $(NORMAL_DIR)
	@cp $(NORMAL_DIR)/miniRT .

bonus:
	make -C $(BONUS_DIR)
	@cp $(BONUS_DIR)/miniRT_bonus .

clean:
	make clean -C $(NORMAL_DIR)

fclean: 
	make fclean -C $(NORMAL_DIR)
	@rm -f miniRT

re: fclean all

clean_bonus:
	make clean -C $(BONUS_DIR)

fclean_bonus: 
	make fclean -C $(BONUS_DIR)
	@rm -f miniRT_bonus

re_bonus: fclean_bonus bonus

both : all bonus

clean_all: clean clean_bonus

fclean_all: fclean fclean_bonus

re_all: re re_bonus

.PHONY: all clean fclean re makelib cleanlib
