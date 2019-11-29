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
	sdl->disp_size = 1;
	sdl->playground_x = 672;
	sdl->playground_y = 1312;
	sdl->playground_offset_x = 0;
	sdl->playground_offset_y = 0;
	sdl->numbers = NULL;
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
	Mix_FreeMusic(sdl->main_theme);
	Mix_FreeChunk(sdl->moving);
	Mix_FreeChunk(sdl->line);
	Mix_FreeChunk(sdl->lost);
	Mix_FreeChunk(sdl->pause);
	Mix_FreeChunk(sdl->landing);
	Mix_FreeChunk(sdl->selecting);
	Mix_FreeChunk(sdl->menu_move);
	SDL_DestroyTexture(sdl->next_tetro);
	for (int i = 0; i < 10; i++)
		SDL_DestroyTexture(sdl->numbers[i]);
	free(sdl->numbers);
	if (sdl->tetros)
		free(sdl->tetros);
	if (sdl->tiles)
		free(sdl->tiles);
	Mix_Quit();
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
	if ((sdl->stored_tetro = IMG_LoadTexture(sdl->renderer,
					"img/stored_background.png")) == NULL)
		failure_exit_program("Converting Stored Background to Texture", sdl);
	if ((sdl->next_tetro = IMG_LoadTexture(sdl->renderer,
					"img/next_background.png")) == NULL)
		failure_exit_program("Converting Next Tetro Background to Texture", sdl);
	if ((sdl->playground = IMG_LoadTexture(sdl->renderer,
					"img/playground.png")) == NULL)
		failure_exit_program("Converting playground to Texture", sdl);
	if ((sdl->score_window = IMG_LoadTexture(sdl->renderer,
					"img/score_background.png")) == NULL)
		failure_exit_program("Converting score to Texture", sdl);
	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_copy(sdl, sdl->renderer, sdl->playground, NULL, &dst);
	SDL_RenderPresent(sdl->renderer);
	SDL_SetRenderTarget(sdl->renderer, NULL);
}

void			clean_tetris_struct(t_tetris *tetris)
{
	t_spawning	*tmp;

	if (tetris->board)
	{
		for (int i = 0; i < 24; i++)
			free(tetris->board[i]);
		free(tetris->board);
	}
	if (tetris->curr_tetro)
	{
		for (int i = 0; i < tetris->curr_len_y; i++)
			free(tetris->curr_tetro[i]);
		free(tetris->curr_tetro);
	}
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
	tetris->level = 0;
	tetris->level_cap = 100;
	tetris->lost = 0;
	tetris->curr_tetro = NULL;
	tetris->spawned = 0;
	tetris->stored_tetro_type = -1;
	tetris->has_stored = 0;
	tetris->retreive_stored_tetro = 0;
	tetris->turn_speed = 500;
	tetris->next_tetro = (t_spawning*)malloc(sizeof(t_spawning));;
	fill_tetris_list_next_tetro(tetris->next_tetro);
}

void			retreive_window_resolution(t_sdl *sdl)
{
	SDL_DisplayMode	display;

	if (SDL_GetDesktopDisplayMode(0, &display) != 0)
		failure_exit_program("Getting Display Mode", sdl);
	if (display.w == 1600 && display.h == 900)
		sdl->disp_size = 1.25;
	else if (display.w == 1920 && display.h == 1080)
		sdl->disp_size = 1.5;
	sdl->window_w = display.w;
	sdl->window_h = display.h;
	sdl->playground_x = 336 * sdl->disp_size;
	sdl->playground_y = 656 * sdl->disp_size;
	sdl->playground_offset_x = (display.w / 2) - (sdl->playground_x / 2);
	sdl->playground_offset_y = (display.h / 2) - (sdl->playground_y / 2);
	sdl->tetro_x = sdl->playground_offset_x + (8 * sdl->disp_size);
	sdl->tetro_y = sdl->playground_offset_y + (8 * sdl->disp_size);
	sdl->tetro_size = 32 * sdl->disp_size;
}

void			load_numbers_img(t_sdl *sdl)
{
	sdl->numbers = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10);
	sdl->numbers[0] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[0],
				"img/numbers/zero.png");
	sdl->numbers[1] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[1],
				"img/numbers/one.png");
	sdl->numbers[2] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[2],
				"img/numbers/two.png");
	sdl->numbers[3] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[3],
				"img/numbers/three.png");
	sdl->numbers[4] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[4],
				"img/numbers/four.png");
	sdl->numbers[5] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[5],
				"img/numbers/five.png");
	sdl->numbers[6] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[6],
				"img/numbers/six.png");
	sdl->numbers[7] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[7],
				"img/numbers/seven.png");
	sdl->numbers[8] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[8],
				"img/numbers/eight.png");
	sdl->numbers[9] = SDL_load_texture(sdl, sdl->renderer, sdl->numbers[9],
				"img/numbers/nine.png");
}

void			load_menus_img(t_sdl *sdl)
{
	if ((sdl->menu = SDL_load_texture(sdl, sdl->renderer, sdl->menu, "img/menu.png"))
			== NULL)
		failure_exit_program("Loading Menu Texture", sdl);
	if ((sdl->pause_menu_play = SDL_load_texture(sdl, sdl->renderer, sdl->pause_menu_play,
					"img/pause_menu_play.png")) == NULL)
		failure_exit_program("Loading Pause Play Texture", sdl);
	if ((sdl->pause_menu_options = SDL_load_texture(sdl, sdl->renderer, sdl->pause_menu_options,
					"img/pause_menu_options.png")) == NULL)
		failure_exit_program("Loading Pause Options Texture", sdl);
	if ((sdl->pause_menu_exit = SDL_load_texture(sdl, sdl->renderer, sdl->pause_menu_exit,
					"img/pause_menu_exit.png")) == NULL)
		failure_exit_program("Loading Pause Exit Texture", sdl);
}

void			load_sounds(t_sdl *sdl)
{
	if ((sdl->main_theme = Mix_LoadMUS("sounds/tetris_main_theme.mp3")) == NULL)
		printf("Failure Loading Main Theme Music %s\n", Mix_GetError());
	if ((sdl->moving = Mix_LoadWAV("sounds/sfx_menu_move3.wav")) == NULL)
		printf("Failure Loading Block Rotate Sound %s\n", Mix_GetError());
	if ((sdl->line = Mix_LoadWAV("sounds/sfx_sounds_powerup3.wav")) == NULL)
		printf("Failure Loading Line Remove Sound %s\n", Mix_GetError());
	if ((sdl->lost = Mix_LoadWAV("sounds/sfx_exp_long2.wav")) == NULL)
		printf("Failure Loading Game Over Sound %s\n", Mix_GetError());
	if ((sdl->pause = Mix_LoadWAV("sounds/sfx_sounds_pause3_in.wav")) == NULL)
		printf("Failure Loading Pause Sound %s\n", Mix_GetError());
	if ((sdl->landing = Mix_LoadWAV("sounds/sfx_sounds_impact5.wav")) == NULL)
		printf("Failure Slow Hit Sound %s\n", Mix_GetError());
	if ((sdl->selecting = Mix_LoadWAV("sounds/sfx_menu_select1.wav")) == NULL)
		printf("Failure Loading Menu Select Sound %s\n", Mix_GetError());
	if ((sdl->menu_move = Mix_LoadWAV("sounds/sfx_menu_move3.wav")) == NULL)
		printf("Failure Loading Menu Move Sound %s\n", Mix_GetError());
}

int				main(void)
{
	t_sdl		sdl;
	t_tetris	tetris;
	int			menu_option = -1;

	init_sdl_struct(&sdl);
	SDL_init_window(&sdl);
	SDL_init_renderer(&sdl);
	SDL_init_audio(&sdl);
	SDL_SetRenderDrawBlendMode(sdl.renderer, SDL_BLENDMODE_BLEND);
	SDL_init_img(&sdl);
	retreive_window_resolution(&sdl);
	setup_window_background(&sdl);
	load_sounds(&sdl);
	load_tetros_img(&sdl);
	load_tiles_img(&sdl);
	load_numbers_img(&sdl);
	load_menus_img(&sdl);

	while ((menu_option = launch_game_menu(&sdl)) != 2)
	{
		setup_window_background(&sdl);
//		if (menu_option == 1)
//			launch_option_menu(&sdl);
//		else
//		{
			init_tetris_struct(&tetris);
			load_and_render_playground(&sdl);
			Mix_PlayMusic(sdl.main_theme, -1);
			game_loop(&sdl, &tetris);
//		}
	}

//	clean_tetris_struct(&tetris);
	clean_sdl_struct(&sdl);
	printf("CLEAN EXIT\n");
	return (0);
}
