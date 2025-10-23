# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 00:10:16 by slimvutt          #+#    #+#              #
#    Updated: 2025/10/22 00:10:16 by slimvutt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

#-Wall -Wextra -Werror 
CC = cc
CFLAGS =  -g3 -I. -IMLX42/include
LDFLAGS = MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT = libft/libft.a

SRC =	main.c\
		map_utils/get_map.c\
		map_utils/map_trans.c\
		utils/parse_color.c\
		utils/free_map.c\
		utils/draw_line.c

OBJ = $(SRC:.c=.o)

# ======================= RULES =========================

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C libft bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all


