#include "../includes/tetris.h"

void			init_sdl_struct(t_sdl *sdl)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->img_load = NULL;
	sdl->playground = NULL;
	sdl->tetros = NULL;
	sdl->tiles = NULL;
}

void			clean_sdl_struct(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_DestroyTexture(sdl->playground);
	SDL_DestroyTexture(sdl->tetros->S1);
	SDL_DestroyTexture(sdl->tetros->S2);
	SDL_DestroyTexture(sdl->tetros->I1);
	SDL_DestroyTexture(sdl->tetros->I2);
	SDL_DestroyTexture(sdl->tetros->J1);
	SDL_DestroyTexture(sdl->tetros->J2);
	SDL_DestroyTexture(sdl->tetros->J3);
	SDL_DestroyTexture(sdl->tetros->J4);
	SDL_DestroyTexture(sdl->tetros->L1);
	SDL_DestroyTexture(sdl->tetros->L2);
	SDL_DestroyTexture(sdl->tetros->L3);
	SDL_DestroyTexture(sdl->tetros->L4);
	SDL_DestroyTexture(sdl->tetros->O);
	SDL_DestroyTexture(sdl->tetros->T1);
	SDL_DestroyTexture(sdl->tetros->T2);
	SDL_DestroyTexture(sdl->tetros->T3);
	SDL_DestroyTexture(sdl->tetros->T4);
	SDL_DestroyTexture(sdl->tetros->Z1);
	SDL_DestroyTexture(sdl->tetros->Z2);
	SDL_DestroyTexture(sdl->tiles->blue);
	SDL_DestroyTexture(sdl->tiles->dark_blue);
	SDL_DestroyTexture(sdl->tiles->green);
	SDL_DestroyTexture(sdl->tiles->orange);
	SDL_DestroyTexture(sdl->tiles->purple);
	SDL_DestroyTexture(sdl->tiles->yellow);
	SDL_DestroyTexture(sdl->tiles->blue);
	if (sdl->tetros)
		free(sdl->tetros);
	if (sdl->tiles)
		free(sdl->tiles);
	IMG_Quit();
	SDL_Quit();
}

void			failure_exit_program(char *error, t_sdl *sdl)
{
	fprintf(stderr, "ERROR %s (%s)\n", error, SDL_GetError());
	if (!sdl)
		exit(EXIT_FAILURE);
	clean_sdl_struct(sdl);
	exit(EXIT_FAILURE);
}

void			setup_window_background(t_sdl *sdl)
{
	SDL_Color	bg = DARK_BLUE;

	SDL_apply_color_to_renderer(bg, sdl);
	SDL_render_clear(sdl, sdl->renderer);
	SDL_RenderPresent(sdl->renderer);
}

void			load_and_render_playground(t_sdl *sdl)
{
	SDL_Rect	dst = {708, 48, 504, 984};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_render_target(sdl, sdl->renderer, sdl->playground);
	if ((sdl->playground = IMG_LoadTexture(sdl->renderer,
					"img/big_playground.png")) == NULL)
		failure_exit_program("Converting playground to Texture", sdl);
	SDL_render_clear(sdl, sdl->renderer);
	//	SDL_QueryTexture(sdl->playground, NULL, NULL, &dst.w, &dst.h);
	SDL_render_copy(sdl, sdl->renderer, sdl->playground, NULL, &dst);
	SDL_RenderPresent(sdl->renderer);
	SDL_SetRenderTarget(sdl->renderer, NULL);
}

void			clean_tetris_struct(t_tetris *tetris)
{
	for (int i = 0; i < 20; i++)
		free(tetris->board[i]);
	free(tetris->board);
	for (int i = 0; i < tetris->curr_len_y; i++)
		free(tetris->curr_tetro[i]);
	free(tetris->curr_tetro);
}

void			init_tetris_struct(t_tetris *tetris)
{
	tetris->board = (char**)malloc(sizeof(char*) * (20 + 1));
	for (int i = 0; i < 20; i++)
	{
		tetris->board[i] = (char*)malloc(sizeof(char) * (10 + 1));
		for (int j = 0; j < 10; j++)
			tetris->board[i][j] = '0';
		tetris->board[i][10] = '\0';
	}
	tetris->board[20] = NULL;
	tetris->score = 0;
	tetris->lost = 0;
	tetris->curr_tetro = NULL;
	tetris->spawned = 0;
}

int				main(void)
{
	t_sdl		sdl;
	t_tetris	tetris;

	init_sdl_struct(&sdl);
	SDL_init_window(&sdl);
	SDL_init_renderer(&sdl);
	SDL_init_img(&sdl);
	setup_window_background(&sdl);
	load_and_render_playground(&sdl);
	load_tetros_img(&sdl);
	load_tiles_img(&sdl);
	init_tetris_struct(&tetris);

	game_loop(&sdl, &tetris);

	clean_tetris_struct(&tetris);
	clean_sdl_struct(&sdl);
	printf("CLEAN EXIT\n");
	return (0);
}
