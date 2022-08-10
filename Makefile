SRC_DIR = src/
OBJ_DIR = bin/
INC_DIR = include/
LIBFT_DIR = libs/libft/
MLX_DIR = libs/mlx/

NAME = cub3D

SRCS =	main.c parsing.c parsing_utils.c parsing_bis.c utils.c \
		drawing_utils.c raycasting.c movement.c drawing.c minimap.c \
		textures.c init.c hooks.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPENDS = $(OBJS:.o=.d)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Ofast
INCLUDE = -I$(INC_DIR) -I$(LIBFT_DIR)include -I$(MLX_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm 

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJS)
	@printf "\n$(BLUE)Linking...   $(RESET)"
	@$(CC) $(CLFAGS) $(OBJS) -o $(NAME) $(LFLAGS)
	@printf "$(BLUE)Done\n$(RESET)"

-include $(DEPENDS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(BLUE)→ $(GREEN)Compiling $(subst $(SRC_DIR),,$<)\n$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

$(LIBFT):
	@printf "$(BLUE)→ $(GREEN)Compiling libft...\n$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR) bonus
	@printf "$(BLUE)✔ $(GREEN)Done\n\n$(RESET)"

$(MLX):
	@printf "$(BLUE)→ $(GREEN)Compiling mlx...\n$(RESET)"
	@$(MAKE) -sC $(MLX_DIR) > /dev/null
	@printf "$(BLUE)✔ $(GREEN)Done\n\n$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@printf '$(BLUE)→ $(ORANGE)Removing object files$(RESET)\n'
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf '$(BLUE)→ $(ORANGE)Removing executable$(RESET)\n\n'
	@rm -f $(NAME)

libclean:
	@printf '$(BLUE)→ $(ORANGE)Cleaning libraries: $(LIBFT_DIR) $(MLX_DIR)$(RESET)\n'
	@$(MAKE) -sC $(LIBFT_DIR) fclean
	@$(MAKE) -sC $(MLX_DIR) clean

hclean: fclean libclean

re: fclean all

.PHONY: all clean fclean re libclean libft hclean

# colors

ORANGE = \e[1;33m
BLUE   = \e[1;34m
GREEN  = \e[1;32m
RESET  = \e[0m
