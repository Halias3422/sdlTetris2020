#include "../includes/tetris.h"

void			init_sdl_struct(t_sdl *sdl)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->img_load = NULL;
	sdl->playground = NULL;
	sdl->tetros = NULL;
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
	if (sdl->tetros)
		free(sdl->tetros);
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
	printf("jai set le bg\n");
	if ((sdl->playground = tetro_convert_surface_to_texture(sdl, sdl->playground,
					"img/big_playground.png")) == NULL)
		failure_exit_program("Converting playground to Texture", sdl);
	SDL_render_clear(sdl, sdl->renderer);
	//	SDL_QueryTexture(sdl->playground, NULL, NULL, &dst.w, &dst.h);
	SDL_render_copy(sdl, sdl->renderer, sdl->playground, NULL, &dst);
	SDL_RenderPresent(sdl->renderer);
	SDL_SetRenderTarget(sdl->renderer, NULL);
}
/*
   void			S_tetro_spawn(t_sdl *sdl, t_tetris *tetris)
   {

   }

   void			I_tetro_spawn(t_sdl *sdl, t_tetris *tetris)
   {

   }

   void			J_tetro_spawn(t_sdl *sdl, t_tetris *tetris)
   {

   }

   void			L_tetro_spawn(t_sdl *sdl, t_tetris *tetris)
   {

   }
   */
void			O_tetro_spawn(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 1;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i < 2; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 2);
		tetris->curr_tetro[i][0] = 1;
		tetris->curr_tetro[i][1] = 1;
	}
	tetris->curr_len_x = 2;
	tetris->curr_len_y = 2;
}
/*
   void			T_tetro_spawn(t_sdl *sdl, t_tetris *tetris)
   {

   }

   void			Z_tetro_spawn(t_sdl *sdl, t_tetris *tetris)
   {

   }

   void			get_current_tetro(t_sdl *sdl, t_tetris *tetris, int tetro)
   {
   void		(*tetro_pt[7])(t_sdl *, t_tetris *);

   tetro_pt[0] = &(S_tetro_spawn);
   tetro_pt[1] = &(I_tetro_spawn);
   tetro_pt[2] = &(J_tetro_spawn);
   tetro_pt[3] = &(L_tetro_spawn);
   tetro_pt[4] = &(O_tetro_spawn);
   tetro_pt[5] = &(T_tetro_spawn);
   tetro_pt[6] = &(Z_tetro_spawn);
   (tetro_pt[tetro])(sdl, tetris);
   }
   */
void			spawn_new_tetro(t_sdl *sdl, t_tetris *tetris)
{
	//	int			tetro = -1;

	(void)sdl;
	srand(time(NULL));
	//	tetro = rand() % 7;
	//	get_current_tetro(sdl, tetris, tetro);
	tetris->tetro_type = 4;
	O_tetro_spawn(tetris);
	tetris->act_y = 0;
	tetris->act_x = rand() % ((9 - tetris->offset_right) + 1 -
			tetris->offset_left) + tetris->offset_left;
	printf("tetris->spawning loc = %d offset_left = %d offset_right = %d\n", tetris->act_x,
			tetris->offset_left, tetris->offset_right);
	//tetris->spawned = 1;
}

void			print_tetro_on_screen(t_sdl *sdl, t_tetris *tetris)
{
	SDL_Rect	dst = {708 + 12 + (tetris->act_x * (tetris->curr_len_x * 24)),
				48 + 12 + (tetris->act_y * (tetris->curr_len_y * 24)),
				tetris->curr_len_x * 48, tetris->curr_len_y * 48};


	load_O_tetros(sdl);
	exit(0);
	SDL_render_copy(sdl, sdl->renderer, sdl->tetros->O, NULL, &dst);
	SDL_render_clear(sdl, sdl->renderer);
	SDL_RenderPresent(sdl->renderer);
	SDL_Delay(300);
	SDL_SetRenderTarget(sdl->renderer, NULL);
}

void			game_loop(t_sdl *sdl, t_tetris *tetris)
{
	while (tetris->lost != 1)
	{
		if (tetris->spawned == 0)
			spawn_new_tetro(sdl, tetris);
		print_tetro_on_screen(sdl, tetris);
		while (SDL_PollEvent(&sdl->event))
		{
			if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
				return ;
		}
		SDL_Delay(100);
	}
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
	tetris->board = (int**)malloc(sizeof(int*) * 20);
	for (int i = 0; i < 20; i++)
	{
		tetris->board[i] = (int*)malloc(sizeof(int) * 10);
		for (int j = 0; j < 10; j++)
			tetris->board[i][j] = 0;
	}
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
	init_tetris_struct(&tetris);

	game_loop(&sdl, &tetris);

	clean_tetris_struct(&tetris);
	clean_sdl_struct(&sdl);
	printf("CLEAN EXIT\n");
	return (0);
}
