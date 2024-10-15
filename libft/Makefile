NAME = libft/libft.a

SRCS = src/ft_isalpha.c src/ft_isdigit.c src/ft_isalnum.c src/ft_isascii.c src/ft_isprint.c src/ft_memset.c src/ft_bzero.c \
src/ft_memcpy.c src/ft_memmove.c src/ft_strlcpy.c src/ft_strlcat.c src/ft_toupper.c src/ft_tolower.c src/ft_strrchr.c src/ft_strncmp.c \
src/ft_memchr.c src/ft_memcmp.c src/ft_strnstr.c src/ft_atoi.c src/ft_calloc.c src/ft_strtrim.c src/ft_split.c src/ft_printf.c src/ft_printf_aux.c\
src/ft_itoa.c src/ft_strmapi.c src/ft_striteri.c src/ft_putchar_fd.c src/ft_putstr_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c \
src/get_next_line_utils.c src/get_next_line.c
OBJS = $(SRCS:src/%.c=obj/%.o)



BONUSSRCS = bonus/ft_lstnew_bonus.c bonus/ft_lstadd_front_bonus.c bonus/ft_lstsize_bonus.c bonus/ft_lstlast_bonus.c bonus/ft_lstadd_back_bonus.c \
bonus/ft_lstdelone_bonus.c bonus/ft_lstclear_bonus.c bonus/ft_lstiter_bonus.c bonus/ft_lstmap_bonus.c bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c
BONUSOBJS = $(BONUSSRCS:bonus/%.c=obj/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -Ilibs -fPIC

all: obj libft $(NAME)

libft:
	@mkdir -p libft

obj:
	@mkdir -p obj

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "make all correct"

$(OBJS): obj/%.o:src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUSOBJS)
	@ar rcs $(NAME) $^
	@echo "make bonus correct"

$(BONUSOBJS): obj/%.o:bonus/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@echo "make clean correct"

fclean: clean
	@rm -rf libft
	@echo "make fclean correct"

re: fclean all
	@echo "make re correct"

.PHONY: all clean flean re bonus
