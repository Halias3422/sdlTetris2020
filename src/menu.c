#include "../includes/tetris.h"

void			display_game_menu(t_sdl *sdl, SDL_Rect dst, SDL_Texture *menu,
				int selected)
{
	SDL_Rect	contour = {dst.x + (dst.w / 3) + (16 * sdl->disp_size),
						   dst.y +  (dst.h / 3) + (55 * sdl->disp_size)
							+ (128 *sdl->disp_size) * selected,
						   128 * (sdl->disp_size * 2),
						   32 * (sdl->disp_size * 2)};

	setup_window_background(sdl);
	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_copy(sdl, sdl->renderer, menu, NULL, &dst);
	dst.x += (32 * (sdl->disp_size * 2)) * (selected * 2);
	if (SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, 255) != 0)
		failure_exit_program("Setting Renderer to White", sdl);
	for (int i = 0; i < 3; i++)
	{
		if (SDL_RenderDrawRect(sdl->renderer, &contour) != 0)
			failure_exit_program("Drawing Menu Contour", sdl);
		contour.x -= 1;
		contour.y -= 1;
		contour.w += 2;
		contour.h += 2;
	}
	SDL_RenderPresent(sdl->renderer);
}

int				game_menu_loop(t_sdl *sdl, SDL_Texture *menu, SDL_Rect dst)
{
	int			getting_out = -1;
	SDL_Event	event;
	int			selected = 0;
	int			prev_selected = -1;

	while (getting_out == -1)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
				if (event.key.keysym.sym == SDLK_DOWN)
					selected += 1;
				else if (event.key.keysym.sym == SDLK_UP)
					selected -= 1;
				else if (event.key.keysym.sym == SDLK_RETURN)
					getting_out = selected;
				else if (event.key.keysym.sym == SDLK_ESCAPE)
					return (2);
				if (selected == -1)
					selected = 2;
				else if (selected == 3)
					selected = 0;
		}
		if (prev_selected != selected)
		{
			prev_selected = selected;
			display_game_menu(sdl, dst, menu, selected);
		}
		SDL_Delay(5);
	}
	return (selected);
}

int				launch_game_menu(t_sdl *sdl)
{
	SDL_Texture	*menu = NULL;
	SDL_Rect	dst;

	if ((menu = SDL_load_texture(sdl, sdl->renderer, menu, "img/menu.png"))
			== NULL)
		failure_exit_program("Loading Menu Texture", sdl);
	SDL_QueryTexture(menu, NULL, NULL, &dst.w, &dst.h);
	dst.w *= (sdl->disp_size * 2);
	dst.h *= (sdl->disp_size * 2);
	dst.x = sdl->window_w / 2 - dst.w / 2;
	dst.y = sdl->window_h / 2 - dst.h / 2;
	return (game_menu_loop(sdl, menu, dst));
}
