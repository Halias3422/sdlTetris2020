#include "../includes/tetris.h"

void			load_I_tetros(t_sdl *sdl)
{
	if ((sdl->tetros->I1 = IMG_LoadTexture(sdl->renderer,
			"img/I_tetro/I1_blue_tetro.png")) == NULL)
		failure_exit_program("Loading I_tetro onto Texture", sdl);
	if ((sdl->tetros->I2 = IMG_LoadTexture(sdl->renderer,
			"img/I_tetro/I2_blue_tetro.png")) == NULL)
		failure_exit_program("Loading I_tetro onto Texture", sdl);
}

void			load_J_tetros(t_sdl *sdl)
{
	if ((sdl->tetros->J1 = IMG_LoadTexture(sdl->renderer,
			"img/J_tetro/J1_blue_tetro.png")) == NULL)
		failure_exit_program("Loading J_tetro onto Texture", sdl);
	if ((sdl->tetros->J2 = IMG_LoadTexture(sdl->renderer,
			"img/J_tetro/J2_blue_tetro.png")) == NULL)
		failure_exit_program("Loading J_tetro onto Texture", sdl);
	if ((sdl->tetros->J3 = IMG_LoadTexture(sdl->renderer,
			"img/J_tetro/J3_blue_tetro.png")) == NULL)
		failure_exit_program("Loading J_tetro onto Texture", sdl);
	if ((sdl->tetros->J4 = IMG_LoadTexture(sdl->renderer,
			"img/J_tetro/J4_blue_tetro.png")) == NULL)
		failure_exit_program("Loading J_tetro onto Texture", sdl);
}

void			load_L_tetros(t_sdl *sdl)
{
	if ((sdl->tetros->L1 = IMG_LoadTexture(sdl->renderer,
			"img/L_tetro/L1_orange_tetro.png")) == NULL)
		failure_exit_program("Loading L_tetro onto Texture", sdl);
	if ((sdl->tetros->L2 = IMG_LoadTexture(sdl->renderer,
			"img/L_tetro/L2_orange_tetro.png")) == NULL)
		failure_exit_program("Loading L_tetro onto Texture", sdl);
	if ((sdl->tetros->L3 = IMG_LoadTexture(sdl->renderer,
			"img/L_tetro/L3_orange_tetro.png")) == NULL)
		failure_exit_program("Loading L_tetro onto Texture", sdl);
	if ((sdl->tetros->L4 = IMG_LoadTexture(sdl->renderer,
			"img/L_tetro/L4_orange_tetro.png")) == NULL)
		failure_exit_program("Loading L_tetro onto Texture", sdl);
}

void			load_O_tetros(t_sdl *sdl)
{
	if ((sdl->tetros->O = IMG_LoadTexture(sdl->renderer,
					"img/O_tetro/O1_yellow_tetro.png")) == NULL)
		failure_exit_program("Loading O_tetro onto Texture", sdl);
	SDL_SetTextureBlendMode(sdl->tetros->O, SDL_BLENDMODE_BLEND);
}

void			load_S_tetros(t_sdl *sdl)
{
	if ((sdl->tetros->S1 = IMG_LoadTexture(sdl->renderer,
			"img/S_tetro/S1_green_tetro.png")) == NULL)
		failure_exit_program("Loading S_tetro onto Texture", sdl);
	if ((sdl->tetros->S2 = IMG_LoadTexture(sdl->renderer,
			"img/S_tetro/S2_green_tetro.png")) == NULL)
		failure_exit_program("Loading S_tetro onto Texture", sdl);
}

void			load_T_tetros(t_sdl *sdl)
{
	if ((sdl->tetros->T1 = IMG_LoadTexture(sdl->renderer,
			"img/T_tetro/T1_purple_tetro.png")) == NULL)
		failure_exit_program("Loading T_tetro onto Texture", sdl);
	if ((sdl->tetros->T2 = IMG_LoadTexture(sdl->renderer,
			"img/T_tetro/T2_purple_tetro.png")) == NULL)
		failure_exit_program("Loading T_tetro onto Texture", sdl);
	if ((sdl->tetros->T3 = IMG_LoadTexture(sdl->renderer,
			"img/T_tetro/T3_purple_tetro.png")) == NULL)
		failure_exit_program("Loading T_tetro onto Texture", sdl);
	if ((sdl->tetros->T4 = IMG_LoadTexture(sdl->renderer,
			"img/T_tetro/T4_purple_tetro.png")) == NULL)
		failure_exit_program("Loading T_tetro onto Texture", sdl);
}

void			load_Z_tetros(t_sdl *sdl)
{
	if ((sdl->tetros->Z1 = IMG_LoadTexture(sdl->renderer,
			"img/Z_tetro/Z1_red_tetro.png")) == NULL)
		failure_exit_program("Loading Z_tetro onto Texture", sdl);
	if ((sdl->tetros->Z2 = IMG_LoadTexture(sdl->renderer,
			"img/Z_tetro/Z2_red_tetro.png")) == NULL)
		failure_exit_program("Loading Z_tetro onto Texture", sdl);
}

void			load_tetros_img(t_sdl *sdl)
{
	sdl->tetros = (t_tetros*)malloc(sizeof(t_tetros));
	load_I_tetros(sdl);
	load_J_tetros(sdl);
	load_L_tetros(sdl);
	load_O_tetros(sdl);
	load_S_tetros(sdl);
	load_T_tetros(sdl);
	load_Z_tetros(sdl);
}
