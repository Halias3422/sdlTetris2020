#include "../includes/tetris.h"

void			load_blue_tile(t_sdl *sdl)
{
	if ((sdl->tiles->blue = IMG_LoadTexture(sdl->renderer,
					"img/tiles/blue_tetro.png")) == NULL)
		failure_exit_program("Loading Yellow tile", sdl);
}

void			load_dark_blue_tile(t_sdl *sdl)
{
	if ((sdl->tiles->dark_blue = IMG_LoadTexture(sdl->renderer,
					"img/tiles/dark_blue_tetro.png")) == NULL)
		failure_exit_program("Loading Yellow tile", sdl);

}

void			load_green_tile(t_sdl *sdl)
{
	if ((sdl->tiles->green = IMG_LoadTexture(sdl->renderer,
					"img/tiles/green_tetro.png")) == NULL)
		failure_exit_program("Loading Yellow tile", sdl);

}

void			load_orange_tile(t_sdl *sdl)
{
	if ((sdl->tiles->orange = IMG_LoadTexture(sdl->renderer,
					"img/tiles/orange_tetro.png")) == NULL)
		failure_exit_program("Loading Yellow tile", sdl);

}

void			load_purple_tile(t_sdl *sdl)
{
	if ((sdl->tiles->purple = IMG_LoadTexture(sdl->renderer,
					"img/tiles/purple_tetro.png")) == NULL)
		failure_exit_program("Loading Yellow tile", sdl);

}

void			load_red_tile(t_sdl *sdl)
{
	if ((sdl->tiles->red = IMG_LoadTexture(sdl->renderer,
					"img/tiles/red_tetro.png")) == NULL)
		failure_exit_program("Loading Yellow tile", sdl);
}

void			load_yellow_tile(t_sdl *sdl)
{
	if ((sdl->tiles->yellow = IMG_LoadTexture(sdl->renderer,
					"img/tiles/yellow_tetro.png")) == NULL)
		failure_exit_program("Loading Yellow tile", sdl);
}

void			load_white_tile(t_sdl *sdl)
{
	if ((sdl->tiles->white = IMG_LoadTexture(sdl->renderer,
					"img/tiles/white_tetro.png")) == NULL)
		failure_exit_program("Loading White Tile", sdl);
}

void			load_tiles_img(t_sdl *sdl)
{
	sdl->tiles = (t_tiles*)malloc(sizeof(t_tiles));
	load_blue_tile(sdl);
	load_dark_blue_tile(sdl);
	load_green_tile(sdl);
	load_orange_tile(sdl);
	load_purple_tile(sdl);
	load_red_tile(sdl);
	load_yellow_tile(sdl);
	load_white_tile(sdl);
}
