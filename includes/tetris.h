#ifndef TETRIS_H
# define TETRIS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

# define DARK_BLUE {0, 25, 51, 255}

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

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Event			event;
	SDL_Surface			*img_load;
	SDL_Texture			*playground;
	struct s_tetros		*tetros;

}						t_sdl;

//	MAIN_C

void			failure_exit_program(char *error, t_sdl *sdl);

//	SDL_FUNCTIONS_C

void			SDL_render_clear(t_sdl *sdl);
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
SDL_Texture		*tetro_convert_surface_to_texture(t_sdl *sdl,
				SDL_Texture *texture, char *img_path);

#endif
