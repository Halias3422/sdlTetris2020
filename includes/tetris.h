#ifndef TETRIS_H
# define TETRIS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

# define DARK_BLUE {0, 25, 51, 255}

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*img_load;
	SDL_Texture			*S_tetro;
	SDL_Texture			*I_tetro;
	SDL_Texture			*J_tetro;
	SDL_Texture			*L_tetro;
	SDL_Texture			*O_tetro;
	SDL_Texture			*T_tetro;
	SDL_Texture			*Z_tetro;

}						t_sdl;

#endif
