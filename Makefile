.PHONY: libft minilibx all clean fclean re

SRCS =	src/init.c\
		src/main.c\
		src/graphic_math.c\
		src/graphic.c\
		src/key_action.c\
		src/my_math.c\
		src/my_math2.c\
		src/my_mlx.c\
		src/player_action.c\
		src/wall_find.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
		src/wall_utils.c\
		src/utils.c\
		src/map_parsing.c\
		src/node.c\
		src/texture.c\
		src/color.c\
		src/error.c


NAME = Cub3D
GCC_FLAG = -g -fsanitize=address # -Wall -Werror -Wextra
CC = gcc $(GCC_FLAG)

OBJS = $(SRCS:.c=.o)

all: libft minilibx $(NAME)

libft:
	make -C libft/

minilibx:
	make -C mlx


$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -Lmlx -lmlx -framework OPENGL -framework Appkit -Llibft -lft


clean:
	rm -f $(OBJS)
	make -C libft/ clean
	make -C mlx clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C mlx clean

re: fclean all
