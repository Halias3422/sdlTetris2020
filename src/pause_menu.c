#include "../includes/tetris.h"

void			draw_contour_around_selected_menu(t_sdl *sdl, int selected,
				SDL_Rect dst, int pos_y)
{
	SDL_Rect	contour = {dst.x, (selected + 1) * pos_y, dst.w, dst.h};

	if (SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, 255) != 0)
		failure_exit_program("Setting Renderer to White", sdl);
	for (int i = 0; i < 3; i++)
	{
		if (SDL_RenderDrawRect(sdl->renderer, &contour) != 0)
			failure_exit_program("Drawing Pause Menu Contour", sdl);
		contour.x += 1;
		contour.y += 1;
		contour.w -= 2;
		contour.h -= 2;
	}
}

void			display_three_menu_boxes(t_sdl *sdl, t_tetris *tetris, int selected)
{
	int			pos_y = (sdl->window_h / 9) * 2;
	SDL_Rect	dst;
	Uint8		r = 0, g = 0, b = 0, a = 210;
	SDL_Rect	background = {0, 0, sdl->window_w, sdl->window_h};

	SDL_render_clear(sdl, sdl->renderer);
	print_tetro_on_screen(sdl, tetris);
	if (SDL_SetRenderDrawColor(sdl->renderer, r, g, b, a) != 0)
		failure_exit_program("Setting Pause Menu BG Color", sdl);

	if (SDL_RenderFillRect(sdl->renderer, &background) != 0)
		failure_exit_program("Fill Pause Menu Background", sdl);
	SDL_QueryTexture(sdl->pause_menu_play, NULL, NULL, &dst.w, &dst.h);
	dst.w *= sdl->disp_size * 2;
	dst.h *= sdl->disp_size * 2;
	dst.x = (sdl->window_w / 2) - (dst.w / 2);
	dst.y = pos_y;
	SDL_render_copy(sdl, sdl->renderer, sdl->pause_menu_play, NULL, &dst);
	dst.y += pos_y;
	SDL_render_copy(sdl, sdl->renderer, sdl->pause_menu_options, NULL, &dst);
	dst.y += pos_y;
	SDL_render_copy(sdl, sdl->renderer, sdl->pause_menu_exit, NULL, &dst);
	draw_contour_around_selected_menu(sdl, selected, dst, pos_y);
	SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(sdl->renderer);
}

int				pause_menu(t_sdl *sdl, t_tetris *tetris)
{
	int			getting_out = -1;
	int			prev_selected = -1;
	int			selected = 0;
	SDL_Event	event;

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
				{
					print_tetro_on_screen(sdl, tetris);
					return (0);
				}
				if (selected == -1)
					selected = 2;
				else if (selected == 3)
					selected = 0;
		}
		if (prev_selected != selected)
		{
			prev_selected = selected;
			display_three_menu_boxes(sdl, tetris, selected);
		}
		SDL_Delay(5);
	}
	return (selected);
}
