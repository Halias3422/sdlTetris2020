#include "../includes/tetris.h"

void			init_sdl_struct(t_sdl *sdl)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->img_load = NULL;
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
	SDL_render_clear(sdl);
	SDL_RenderPresent(sdl->renderer);
}

void			close_game_loop(t_sdl *sdl)
{
	while (1)
	{
		while (SDL_PollEvent(&sdl->event))
		{
			if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
				return ;
		}
		SDL_Delay(100);
	}
}

void			load_and_render_playground(t_sdl *sdl)
{
	SDL_Rect	dst = {708, 250, 504, 984};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_SetRenderTarget(sdl->renderer, sdl->playground);
	sdl->playground = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 336, 656);
	sdl->playground = tetro_convert_surface_to_texture(sdl, sdl->playground,
			"img/playground.png");
//	SDL_RenderClear(sdl->renderer);
	SDL_SetRenderTarget(sdl->renderer, NULL);
//	SDL_QueryTexture(sdl->playground, NULL, NULL, &dst.w, &dst.h);
	printf("dst.w = %d dst.h = %d\n", dst.w, dst.h);
	SDL_RenderCopy(sdl->renderer, sdl->playground, NULL, &dst);
	SDL_RenderPresent(sdl->renderer);
}

int				main(void)
{
	t_sdl		sdl;

	init_sdl_struct(&sdl);
	SDL_init_window(&sdl);
	SDL_init_renderer(&sdl);
	SDL_init_img(&sdl);
	setup_window_background(&sdl);
	load_and_render_playground(&sdl);
	load_tetros_img(&sdl);

	close_game_loop(&sdl);
	clean_sdl_struct(&sdl);
	printf("CLEAN EXIT\n");
	return (0);
}
