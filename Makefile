NAME = pipex
SRC = main.c pipex_utils.c pipex_utils_2.c
OBJ = $(SRC:.c=.o)
INC_LIBFT_GNL = -Ilibft/inc_libft/ -Ilibft/inc_gnl/ -Ilibft/inc_ft_printf/
INC = -Iinc/ $(INC_LIBFT_GNL)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LIBFT_INCLUDE = -L./libft -lft
LIBS = $(LIBFT_INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -O3 -c $< -o $@

$(NAME): $(OBJ)
	cd libft && make
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)
	cd libft && make clean

fclean: clean
	$(RM) $(NAME)
	cd libft && make fclean

re: fclean all

clean_rebuild: all clean

.PHONY: all clean fclean .c.o clean_rebuild