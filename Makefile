NAME= tetris

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

SOURCES= main.c load_tetros.c load_tiles.c spawn_tetros_1.c spawn_tetros_2.c spawn_tetros_3.c spawn_tetros_4.c sdl_functions.c \
		 game_loop.c move_tetro.c rotation_tetro.c clear_lines.c menu.c debug.c pause_menu.c
INCLUDES= tetris.h
OBJ_NAME = $(SOURCES:.c=.o)

INC = $(addprefix $(INC_PATH), $(INCLUDES))
SRC = $(addprefix $(SRC_PATH), $(SOURCES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAG += -g #-Wall -Wextra -fsanitize=address

all:
	make $(NAME)

$(NAME): $(OBJ) Makefile
	gcc $(FLAG) -o ${NAME} $(OBJ) -I . -lSDL2 -Wl,-rpath=/usr/local/lib -lSDL2_image -lSDL2_mixer

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	gcc $(FLAG) -g -I $(INC_PATH) -o $@ -c $<

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf ${NAME}

re: fclean all
