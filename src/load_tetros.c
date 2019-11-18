#include "../includes/tetris.h"

SDL_Texture		*tetro_convert_surface_to_texture(t_sdl *sdl,
				SDL_Texture *texture, char *img_path)
{
	if ((sdl->img_load = IMG_Load(img_path)) == NULL)
		failure_exit_program("Loading tetro.png", sdl);
	if ((texture = SDL_CreateTextureFromSurface(sdl->renderer,
					sdl->img_load)) == NULL)
		failure_exit_program("Create s_tetro Texture From Surface", sdl);
	SDL_FreeSurface(sdl->img_load);
	return (texture);
}

void			load_I_tetros(t_sdl *sdl)
{
	sdl->tetros->I1 = tetro_convert_surface_to_texture(sdl, sdl->tetros->I1,
			"img/I_tetro/I1_blue_tetro.png");
	sdl->tetros->I2 = tetro_convert_surface_to_texture(sdl, sdl->tetros->I2,
			"img/I_tetro/I2_blue_tetro.png");
}

void			load_J_tetros(t_sdl *sdl)
{
	sdl->tetros->J1 = tetro_convert_surface_to_texture(sdl, sdl->tetros->J1,
			"img/J_tetro/J1_blue_tetro.png");
	sdl->tetros->J2 = tetro_convert_surface_to_texture(sdl, sdl->tetros->J2,
			"img/J_tetro/J2_blue_tetro.png");
	sdl->tetros->J3 = tetro_convert_surface_to_texture(sdl, sdl->tetros->J3,
			"img/J_tetro/J3_blue_tetro.png");
	sdl->tetros->J4 = tetro_convert_surface_to_texture(sdl, sdl->tetros->J4,
			"img/J_tetro/J4_blue_tetro.png");
}

void			load_L_tetros(t_sdl *sdl)
{
	sdl->tetros->L1 = tetro_convert_surface_to_texture(sdl, sdl->tetros->L1,
			"img/L_tetro/L1_orange_tetro.png");
	sdl->tetros->L2 = tetro_convert_surface_to_texture(sdl, sdl->tetros->L2,
			"img/L_tetro/L2_orange_tetro.png");
	sdl->tetros->L3 = tetro_convert_surface_to_texture(sdl, sdl->tetros->L3,
			"img/L_tetro/L3_orange_tetro.png");
	sdl->tetros->L4 = tetro_convert_surface_to_texture(sdl, sdl->tetros->L4,
			"img/L_tetro/L4_orange_tetro.png");
}

void			load_O_tetros(t_sdl *sdl)
{
	sdl->tetros->O = tetro_convert_surface_to_texture(sdl, sdl->tetros->O,
			"img/O_tetro/O1_yellow_tetro.png");
}

void			load_S_tetros(t_sdl *sdl)
{
	sdl->tetros->S1 = tetro_convert_surface_to_texture(sdl, sdl->tetros->S1,
			"img/S_tetro/S1_green_tetro.png");
	sdl->tetros->S2 = tetro_convert_surface_to_texture(sdl, sdl->tetros->S2,
			"img/S_tetro/S2_green_tetro.png");
}

void			load_T_tetros(t_sdl *sdl)
{
	sdl->tetros->T1 = tetro_convert_surface_to_texture(sdl, sdl->tetros->T1,
			"img/T_tetro/T1_purple_tetro.png");
	sdl->tetros->T2 = tetro_convert_surface_to_texture(sdl, sdl->tetros->T2,
			"img/T_tetro/T2_purple_tetro.png");
	sdl->tetros->T3 = tetro_convert_surface_to_texture(sdl, sdl->tetros->T3,
			"img/T_tetro/T3_purple_tetro.png");
	sdl->tetros->T4 = tetro_convert_surface_to_texture(sdl, sdl->tetros->T4,
			"img/T_tetro/T4_purple_tetro.png");
}

void			load_Z_tetros(t_sdl *sdl)
{
	sdl->tetros->Z1 = tetro_convert_surface_to_texture(sdl, sdl->tetros->Z1,
			"img/Z_tetro/Z1_red_tetro.png");
	sdl->tetros->Z2 = tetro_convert_surface_to_texture(sdl, sdl->tetros->Z2,
			"img/Z_tetro/Z2_red_tetro.png");
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
