#ifndef TETRIS_H
# define TETRIS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

# define DARK_BLUE {0, 25, 51, 255}

typedef struct			s_tetris
{
	char				**board;
	int					score;
	int					lost;
	int					tetro_type;
	int					**curr_tetro;
	int					curr_len_x;
	int					curr_len_y;
	int					offset_left;
	int					offset_right;
	int					act_x;
	int					act_y;
	int					prev_x;
	int					prev_y;
	int					spawned;
	int					old_rotation;
	int					rotation;
}						t_tetris;

typedef struct			s_tetros
{
	SDL_Texture			*S1;
	SDL_Texture			*S2;
	SDL_Texture			*I1;
	SDL_Texture			*I2;
	SDL_Texture			*J1;
	SDL_Texture			*J2;
	SDL_Texture			*J3;
	SDL_Texture			*J4;
	SDL_Texture			*L1;
	SDL_Texture			*L2;
	SDL_Texture			*L3;
	SDL_Texture			*L4;
	SDL_Texture			*O;
	SDL_Texture			*T1;
	SDL_Texture			*T2;
	SDL_Texture			*T3;
	SDL_Texture			*T4;
	SDL_Texture			*Z1;
	SDL_Texture			*Z2;
}						t_tetros;

typedef struct			s_tiles
{
	SDL_Texture			*blue;
	SDL_Texture			*dark_blue;
	SDL_Texture			*green;
	SDL_Texture			*orange;
	SDL_Texture			*purple;
	SDL_Texture			*red;
	SDL_Texture			*yellow;
}						t_tiles;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Event			event;
	SDL_Surface			*img_load;
	SDL_Texture			*playground;
	struct s_tetros		*tetros;
	struct s_tiles		*tiles;
}						t_sdl;

//	MAIN_C

void			failure_exit_program(char *error, t_sdl *sdl);

//	SDL_FUNCTIONS_C

void			SDL_render_target(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture);
void			SDL_render_copy(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest);
void			SDL_render_clear(t_sdl *sdl, SDL_Renderer *renderer);
void			SDL_apply_color_to_renderer(SDL_Color rgba, t_sdl *sdl);
void			SDL_init_renderer(t_sdl *sdl);
void			SDL_init_img(t_sdl *sdl);
void			SDL_init_window(t_sdl *sdl);

//	LOAD_TETROS_C


void			load_I_tetros(t_sdl *sdl);
void			load_T_tetros(t_sdl *sdl);
void			load_Z_tetros(t_sdl *sdl);
void			load_tetros_img(t_sdl *sdl);
void			load_I_tetros(t_sdl *sdl);
void			load_J_tetros(t_sdl *sdl);
void			load_L_tetros(t_sdl *sdl);
void			load_O_tetros(t_sdl *sdl);

//	LOAD_TILES_C

void			load_tiles_img(t_sdl *sdl);
void			load_blue_tile(t_sdl *sdl);
void			load_dark_blue_tile(t_sdl *sdl);
void			load_green_tile(t_sdl *sdl);
void			load_orange_tile(t_sdl *sdl);
void			load_purple_tile(t_sdl *sdl);
void			load_red_tile(t_sdl *sdl);
void			load_yellow_tile(t_sdl *sdl);

//	SPAWN_TETROS_C

void			S_tetro_spawn(t_tetris *tetris);
void			T_tetro_spawn(t_tetris *tetris);
void			I_tetro_spawn(t_tetris *tetris);
void			L_tetro_spawn(t_tetris *tetris);
void			J_tetro_spawn(t_tetris *tetris);
void			O_tetro_spawn(t_tetris *tetris);
void			Z_tetro_spawn(t_tetris *tetris);
void			get_current_tetro(t_tetris *tetris, int tetro);

//	SPAWN_TETROS_2_C

void			Z_tetro_spawn_2(t_tetris *tetris);
void			T_tetro_spawn_2(t_tetris *tetris);
void			L_tetro_spawn_2(t_tetris *tetris);
void			J_tetro_spawn_2(t_tetris *tetris);
void			I_tetro_spawn_2(t_tetris *tetris);
void			get_current_tetro_2(t_tetris *tetris, int tetro);

//	SPAWN_TETROS_3_C

void			Z_tetro_spawn_3(t_tetris *tetris);
void			T_tetro_spawn_3(t_tetris *tetris);
void			L_tetro_spawn_3(t_tetris *tetris);
void			J_tetro_spawn_3(t_tetris *tetris);
void			S_tetro_spawn_3( t_tetris *tetris);
void			I_tetro_spawn_3(t_tetris *tetris);
void			get_current_tetro_3(t_tetris *tetris, int tetro);

//	SPAWN_TETROS_4_C

void			Z_tetro_spawn_4(t_tetris *tetris);
void			T_tetro_spawn_4(t_tetris *tetris);
void			L_tetro_spawn_4(t_tetris *tetris);
void			J_tetro_spawn_4(t_tetris *tetris);
void			S_tetro_spawn_4( t_tetris *tetris);
void			I_tetro_spawn_4(t_tetris *tetris);
void			get_current_tetro_4(t_tetris *tetris, int tetro);

//	GAME_LOOP_C

void			clear_old_tetro_location_on_board(t_tetris *tetris);
int				update_tetris_board_state(t_tetris *tetris);
Uint32			move_tetro_left_right(t_tetris *tetris, Uint32 currently_pressed,
		Uint32 last_pressed, int direction);
Uint32			scan_exit_and_time(const Uint8 *state, Uint32 currently_pressed);
int				scan_keyboard_state(const Uint8 *state, t_tetris *tetris);
void			spawn_new_tetro(t_sdl *sdl, t_tetris *tetris);
void			print_tetro_on_screen(t_sdl *sdl, t_tetris *tetris);
void			game_loop(t_sdl *sdl, t_tetris *tetris);

//	MOVE_TETRO_C

Uint32			move_tetro_left_right(t_tetris *tetris, Uint32 currently_pressed,
				Uint32 last_pressed, int direction);
int				check_if_tetro_can_move_left(t_tetris *tetris);
int				check_if_tetro_can_move_right(t_tetris *tetris);
int				check_if_tetro_can_move_down(t_tetris *tetris);


//	DEBUG_C

void			print_tetro_board(t_tetris *tetris, int len_x, int len_y);
void			print_tetris_board(t_tetris *tetris);
void			check_letters_on_board(t_tetris *tetris);
#endif
