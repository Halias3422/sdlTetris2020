#include "../includes/tetris.h"

void			load_number_zero(t_sdl *sdl)
{
	if ((sdl->numbers->zero = IMG_LoadTexture(sdl->renderer,
					"img/numbers/zero.png")) == NULL)
		failure_exit_program("Loading number zero", sdl);
}

void			load_number_one(t_sdl *sdl)
{
	if ((sdl->numbers->one = IMG_LoadTexture(sdl->renderer,
					"img/numbers/one.png")) == NULL)
		failure_exit_program("Loading number one", sdl);
}

void			load_number_two(t_sdl *sdl)
{
	if ((sdl->numbers->two = IMG_LoadTexture(sdl->renderer,
					"img/numbers/two.png")) == NULL)
		failure_exit_program("Loading number two", sdl);
}

void			load_number_three(t_sdl *sdl)
{
	if ((sdl->numbers->three = IMG_LoadTexture(sdl->renderer,
					"img/numbers/three.png")) == NULL)
		failure_exit_program("Loading number three", sdl);
}

void			load_number_four(t_sdl *sdl)
{
	if ((sdl->numbers->four = IMG_LoadTexture(sdl->renderer,
					"img/numbers/four.png")) == NULL)
		failure_exit_program("Loading number four", sdl);
}

void			load_number_five(t_sdl *sdl)
{
	if ((sdl->numbers->five = IMG_LoadTexture(sdl->renderer,
					"img/numbers/five.png")) == NULL)
		failure_exit_program("Loading number five", sdl);
}

void			load_number_six(t_sdl *sdl)
{
	if ((sdl->numbers->six = IMG_LoadTexture(sdl->renderer,
					"img/numbers/six.png")) == NULL)
		failure_exit_program("Loading number six", sdl);
}

void			load_number_seven(t_sdl *sdl)
{
	if ((sdl->numbers->seven = IMG_LoadTexture(sdl->renderer,
					"img/numbers/seven.png")) == NULL)
		failure_exit_program("Loading number seven", sdl);
}

void			load_number_eight(t_sdl *sdl)
{
	if ((sdl->numbers->eight = IMG_LoadTexture(sdl->renderer,
					"img/numbers/eight.png")) == NULL)
		failure_exit_program("Loading number eight", sdl);
}

void			load_number_nine(t_sdl *sdl)
{
	if ((sdl->numbers->nine = IMG_LoadTexture(sdl->renderer,
					"img/numbers/nine.png")) == NULL)
		failure_exit_program("Loading number nine", sdl);
}

void			load_numbers_img(t_sdl *sdl)
{
	sdl->numbers = (t_numbers*)malloc(sizeof(t_numbers));
	load_number_zero(sdl);
	load_number_one(sdl);
	load_number_two(sdl);
	load_number_three(sdl);
	load_number_four(sdl);
	load_number_five(sdl);
	load_number_six(sdl);
	load_number_seven(sdl);
	load_number_eight(sdl);
	load_number_nine(sdl);
}
