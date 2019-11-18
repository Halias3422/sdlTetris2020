#include "../includes/tetris.h"

void			init_sdl_struct(t_sdl *sdl)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->img_load = NULL;
}

void			clean_sdl_struct(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyTexture(sdl->S_tetro);
	SDL_DestroyTexture(sdl->I_tetro);
	SDL_DestroyTexture(sdl->J_tetro);
	SDL_DestroyTexture(sdl->L_tetro);
	SDL_DestroyTexture(sdl->O_tetro);
	SDL_DestroyTexture(sdl->T_tetro);
	SDL_DestroyTexture(sdl->Z_tetro);
	SDL_DestroyWindow(sdl->window);
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

void			SDL_init_window(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
			failure_exit_program("Initialization SDL WINDOW", sdl);
	if ((sdl->window = SDL_CreateWindow("SUCH AMAZING TETRIS, SUCH WOW",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080,
				SDL_WINDOW_SHOWN)) == NULL)
		failure_exit_program("Creating sdl->window", sdl);
}

void			SDL_init_renderer(t_sdl *sdl)
{
	if ((sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
					SDL_RENDERER_ACCELERATED)) == NULL)
		failure_exit_program("Creating Window Renderer", sdl);
}

void			SDL_apply_color_to_renderer(SDL_Color rgba, t_sdl *sdl)
{
	if ((SDL_SetRenderDrawColor(sdl->renderer, rgba.r, rgba.g, rgba.b, rgba.a))
			!= 0)
		failure_exit_program("Rendering Color", sdl);
}

void			SDL_render_clear(t_sdl *sdl)
{
	if ((SDL_RenderClear(sdl->renderer)) != 0)
		failure_exit_program("Clearing Render With Color", sdl);
}

SDL_Texture		*tetro_convert_surface_to_texture(t_sdl *sdl,
				SDL_Texture *texture, char *img_path)
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		failure_exit_program("Initializing IMAGES", sdl);
	if ((sdl->img_load = IMG_Load(img_path)) == NULL)
		failure_exit_program("Loading tetro.png", sdl);
	if ((texture = SDL_CreateTextureFromSurface(sdl->renderer,
					sdl->img_load)) == NULL)
		failure_exit_program("Create s_tetro Texture From Surface", sdl);
	SDL_FreeSurface(sdl->img_load);
	return (texture);
}

void			load_tetros_img(t_sdl *sdl)
{
	sdl->S_tetro = tetro_convert_surface_to_texture(sdl, sdl->S_tetro,
			"img/S_green_tetro.png");
	sdl->I_tetro = tetro_convert_surface_to_texture(sdl, sdl->S_tetro,
			"img/I_blue_tetro.png");
	sdl->J_tetro = tetro_convert_surface_to_texture(sdl, sdl->S_tetro,
			"img/J_blue_tetro.png");
	sdl->L_tetro = tetro_convert_surface_to_texture(sdl, sdl->S_tetro,
			"img/L_orange_tetro.png");
	sdl->O_tetro = tetro_convert_surface_to_texture(sdl, sdl->S_tetro,
			"img/O_yellow_tetro.png");
	sdl->T_tetro = tetro_convert_surface_to_texture(sdl, sdl->S_tetro,
			"img/T_purple_tetro.png");
	sdl->Z_tetro = tetro_convert_surface_to_texture(sdl, sdl->S_tetro,
			"img/Z_red_tetro.png");

//	SDL_Rect	dst = {0, 0, 64, 96};
//	SDL_RenderClear(sdl->renderer);
//	if (SDL_RenderCopy(sdl->renderer, sdl->Z_tetro, NULL, &dst) != 0)
//		failure_exit_program("Render Copy Of s_tetro Texture", sdl);
//	SDL_RenderPresent(sdl->renderer);
}

void			setup_window_background(t_sdl *sdl)
{
	SDL_Color	bg = DARK_BLUE;

	SDL_apply_color_to_renderer(bg, sdl);
	SDL_render_clear(sdl);
	SDL_RenderPresent(sdl->renderer);
}

int				main(void)
{
	t_sdl		sdl;

	init_sdl_struct(&sdl);
	SDL_init_window(&sdl);
	SDL_init_renderer(&sdl);
	load_tetros_img(&sdl);
//	setup_window_background(&sdl);

	SDL_Delay(1000);
	clean_sdl_struct(&sdl);
	printf("CLEAN EXIT\n");
	return (0);
}
