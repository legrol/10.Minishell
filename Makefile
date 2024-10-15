CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude -Ilibft/libs -lreadline
SRC = src/ft_cd.c src/ft_cmdexe.c src/ft_env.c src/ft_find_dir.c src/ft_path.c src/main.c
OBJ = $(SRC:src/%.c=obj/%.o)
NAME = minishell
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

obj:
	@mkdir -p obj

$(NAME): obj $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME) $(CFLAGS)
	@echo "$(NAME) compiled successfully"

$(OBJ): obj/%.o: src/%.c | obj
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "make clean done"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "make fclean done"

re: fclean all

.PHONY: all clean fclean re


