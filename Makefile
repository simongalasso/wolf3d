NAME 		= wolf3d

CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror -g #-fsanitize=address

ID_UN 		= $(shell id -un)
SRC_PATH 	= srcs/
OBJ_PATH 	= objs/
INC_PATH	= includes/ libft/includes/
LIBFT 		= libft/

YELLOW      = "\\033[33m"
BLUE        = "\\033[34m"
RED         = "\\033[31m"
WHITE       = "\\033[0m"
CYAN        = "\\033[36m"
GREEN       = "\\033[32m"
BOLD        = "\\033[1m"
PINK        = "\\033[95m"

SDL_NUM		= $(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2/ | tail -1)
TTF_NUM		= $(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/ | tail -1)
IMG_NUM		= $(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_image/ | tail -1)
MIX_NUM		= $(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/ | tail -1)

INC_PATH	+= /Users/$(ID_UN)/.brew/Cellar/sdl2/$(SDL_NUM)/include/ \
			   /Users/$(ID_UN)/.brew/Cellar/sdl2/$(SDL_NUM)/include/SDL2/ \
			   /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/$(TTF_NUM)/include/ \
			   /Users/$(ID_UN)/.brew/Cellar/sdl2_image/$(IMG_NUM)/include/ \
			   /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/$(MIX_NUM)/include/ \

SRC_NAME 	= main.c \
			  ft_srfdel.c \
			  ft_get_map.c \
			  ft_init_data.c \
			  ft_get_events.c \
			  ft_rc_wolfcalc.c \
			  ft_minimap.c \
			  ft_utils.c \
			  ft_set_infos.c \
			  ft_set_interface.c \

OBJ_NAME = $(SRC_NAME:.c=.o)
LSDL2 	 = -L/Users/$(ID_UN)/.brew/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into %-50s\r" $(NAME)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT) -lft $(INC) $(LSDL2)
	@printf "$(GREEN)[OK]$(WHITE) %s has been well compiled\n" $(NAME)

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
	@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile
	@printf "$(CYAN)[WAIT]$(WHITE) Compiling into .o %-50s\r" $@
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJ_PATH)
	@printf "$(GREEN)[OK]$(WHITE) Clean done\n"

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@printf "$(GREEN)[OK]$(WHITE) Fclean done\n"

re: fclean all

.PHONY: all re clean fclean
