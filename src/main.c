#include "../includes/tetris.h"

void			init_sdl_struct(t_sdl *sdl)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->img_load = NULL;
	sdl->playground = NULL;
	sdl->stored_tetro = NULL;
	sdl->tetros = NULL;
	sdl->tiles = NULL;
	sdl->disp_size = 0.5;
	sdl->playground_x = 672;
	sdl->playground_y = 1312;
	sdl->playground_offset_x = 0;
	sdl->playground_offset_y = 0;
	sdl->tetro_x = 0;
	sdl->tetro_y = 0;
	sdl->tetro_size = 64;
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
	SDL_DestroyTexture(sdl->tiles->white);
	SDL_DestroyTexture(sdl->stored_tetro);
	SDL_DestroyTexture(sdl->next_tetro);
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
	SDL_Rect	dst = {sdl->playground_offset_x,
	   			       sdl->playground_offset_y,
					   sdl->playground_x,
					   sdl->playground_y};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_render_target(sdl, sdl->renderer, sdl->playground);
	if ((sdl->stored_tetro = IMG_LoadTexture(sdl->renderer,
					"img/stored_background.png")) == NULL)
		failure_exit_program("Converting Stored Background to Texture", sdl);
	if ((sdl->next_tetro = IMG_LoadTexture(sdl->renderer,
					"img/next_background.png")) == NULL)
		failure_exit_program("Converting Next Tetro Background to Texture", sdl);
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
	t_spawning	*tmp;

	for (int i = 0; i < 24; i++)
	free(tetris->board[i]);
	free(tetris->board);
	for (int i = 0; i < tetris->curr_len_y; i++)
		free(tetris->curr_tetro[i]);
	free(tetris->curr_tetro);
	while (tetris->next_tetro != NULL)
	{
		tmp = tetris->next_tetro;
		tetris->next_tetro = tetris->next_tetro->next;
		free(tmp);
	}

}

void			fill_tetris_list_next_tetro(t_spawning *next_tetro)
{
	t_spawning	*tmp;
	int			prev_type;

	srand(time(NULL));
	next_tetro->tetro_type = rand() % 7;
	prev_type = next_tetro->tetro_type;
	for (int i = 0; i < 3; i++)
	{
		tmp = (t_spawning*)malloc(sizeof(t_spawning));
		tmp->tetro_type = rand() % 7;
		while (tmp->tetro_type == prev_type)
			tmp->tetro_type = rand() % 7;
		prev_type = tmp->tetro_type;
		tmp->next = NULL;
		next_tetro->next = tmp;
		next_tetro = next_tetro->next;
	}
}

void			init_tetris_struct(t_tetris *tetris)
{
	tetris->board = (char**)malloc(sizeof(char*) * (24 + 1));
	for (int i = 0; i < 24; i++)
	{
		tetris->board[i] = (char*)malloc(sizeof(char) * (10 + 1));
		for (int j = 0; j < 10; j++)
			tetris->board[i][j] = '0';
		tetris->board[i][10] = '\0';
	}
	tetris->board[24] = NULL;
	tetris->score = 0;
	tetris->lost = 0;
	tetris->curr_tetro = NULL;
	tetris->spawned = 0;
	tetris->stored_tetro_type = -1;
	tetris->retreive_stored_tetro = 0;
	tetris->next_tetro = (t_spawning*)malloc(sizeof(t_spawning));;
	fill_tetris_list_next_tetro(tetris->next_tetro);
}

void			retreive_window_resolution(t_sdl *sdl)
{
	SDL_DisplayMode	display;

	if (SDL_GetDesktopDisplayMode(0, &display) != 0)
		failure_exit_program("Getting Display Mode", sdl);
	if (display.w == 1600 && display.h == 900)
		sdl->disp_size = 0.5;
	else if (display.w == 1920 && display.h == 1080)
		sdl->disp_size = 0.75;
	sdl->playground_x = 672 * sdl->disp_size;
	sdl->playground_y = 1312 * sdl->disp_size;
	sdl->playground_offset_x = (display.w / 2) - (sdl->playground_x / 2);
	sdl->playground_offset_y = (display.h / 2) - (sdl->playground_y / 2);
	sdl->tetro_x = sdl->playground_offset_x + (16 * sdl->disp_size);
	sdl->tetro_y = sdl->playground_offset_y + (16 * sdl->disp_size);
	sdl->tetro_size = 65 * sdl->disp_size;
}

int				main(void)
{
	t_sdl		sdl;
	t_tetris	tetris;

	init_sdl_struct(&sdl);
	SDL_init_window(&sdl);
	SDL_init_renderer(&sdl);
	SDL_init_img(&sdl);
	retreive_window_resolution(&sdl);
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
