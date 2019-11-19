#include "../includes/tetris.h"

void			print_tetris_board(t_tetris *tetris)
{
	int i = 0;

	printf("\n");
	while (tetris->board[i])
	{
		printf("%s\n", tetris->board[i]);
		i++;
	}
}

void			print_tetro_board(t_tetris *tetris, int len_x, int len_y)
{
	printf("\n");
	for (int i = 0; i < len_y; i++)
	{
		for (int j = 0; j < len_x; j++)
			printf("%d ", tetris->curr_tetro[i][j]);
		printf("\n");
	}

}
void			spawn_new_tetro(t_sdl *sdl, t_tetris *tetris)
{

	tetris->tetro_type = -1;
	srand(time(NULL));
	tetris->tetro_type = rand() % 7;
	get_current_tetro(tetris, tetris->tetro_type);
	tetris->act_y = 0;
	tetris->act_x = rand() % ((9 - tetris->offset_right) + 1 -
			tetris->offset_left) + tetris->offset_left;
	tetris->spawned = 1;
	tetris->prev_x = tetris->act_x;
	tetris->prev_y = tetris->act_y;
}

SDL_Texture		*get_current_tetro_texture(t_sdl *sdl, t_tetris *tetris)
{
	switch (tetris->tetro_type)
	{
		case 0:
			return (sdl->tetros->S1);
		case 1:
			return (sdl->tetros->I1);
		case 2:
			return (sdl->tetros->J1);
		case 3:
			return (sdl->tetros->L1);
		case 4:
			return (sdl->tetros->O);
		case 5:
			return (sdl->tetros->T1);
		case 6:
			return (sdl->tetros->Z1);
	}
	failure_exit_program("Could Not Retreive Current Tetro Texture", sdl);
	return (NULL);
}

void			render_all_grounded_tetros(t_sdl *sdl, t_tetris *tetris)
{
	int			i = 0;
	SDL_Rect	dst = {708 + 12, 48 + 12, 48, 48};

	while (tetris->board[i])
	{
		int j = 0;
		dst.x = 708 + 12;
		while (tetris->board[i][j])
		{
			if (tetris->board[i][j] == 'B')
				SDL_render_copy(sdl, sdl->renderer, sdl->tiles->blue, NULL, &dst);
			else if (tetris->board[i][j] == 'C')
				SDL_render_copy(sdl, sdl->renderer, sdl->tiles->dark_blue, NULL, &dst);
			else if (tetris->board[i][j] == 'A')
				SDL_render_copy(sdl, sdl->renderer, sdl->tiles->green, NULL, &dst);
			else if (tetris->board[i][j] == 'D')
				SDL_render_copy(sdl, sdl->renderer, sdl->tiles->orange, NULL, &dst);
			else if (tetris->board[i][j] == 'F')
				SDL_render_copy(sdl, sdl->renderer, sdl->tiles->purple, NULL, &dst);
			else if (tetris->board[i][j] == 'G')
				SDL_render_copy(sdl, sdl->renderer, sdl->tiles->red, NULL, &dst);
			else if (tetris->board[i][j] == 'E')
				SDL_render_copy(sdl, sdl->renderer, sdl->tiles->yellow, NULL, &dst);
			dst.x += 48;
			j++;
		}
	dst.y += 48;
	i++;
	}
}

void			print_tetro_on_screen(t_sdl *sdl, t_tetris *tetris)
{
	SDL_Rect	playground_dst = {708, 48, 504, 984};
	SDL_Rect	dst = {708 + 12 + (((tetris->act_x + 1) * 48) - 48),
		48 + 12 + (((tetris->act_y + 1) * 48) - 48),
		tetris->curr_len_x * 48,
		tetris->curr_len_y * 48};

	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_copy(sdl, sdl->renderer, sdl->playground, NULL, &playground_dst);
	SDL_render_copy(sdl, sdl->renderer, get_current_tetro_texture(sdl, tetris),
			NULL, &dst);
	render_all_grounded_tetros(sdl, tetris);
	SDL_RenderPresent(sdl->renderer);
}

int			check_if_tetro_can_move_left(t_tetris *tetris)
{
	if (tetris->act_x - tetris->offset_left - 1 < 0)
		return (0);
	for (int y = tetris->act_y; y < tetris->act_y + tetris->curr_len_y; y++)
	{
		for (int x = tetris->act_x; x < tetris->act_x + tetris->curr_len_x; x++)
		{
			if (tetris->board[y][x - 1] != '0' && tetris->board[y][x - 1] != '1')
				return (0);
		}
	}
	return (1);
}

int			check_if_tetro_can_move_right(t_tetris *tetris)
{
	if (tetris->act_x + tetris->offset_right + 1 > 9)
		return (0);
	for (int y = tetris->act_y; y < tetris->act_y + tetris->curr_len_y; y++)
	{
		for (int x = tetris->act_x; x < tetris->act_x + tetris->curr_len_x; x++)
		{
			if (tetris->board[y][x + 1] != '0' && tetris->board[y][x + 1] != '1')
				return (0);
		}
	}
	return (1);

}

int			check_if_tetro_can_move_down(t_tetris *tetris)
{
	if (tetris->act_y + tetris->curr_len_y > 19)
		return (0);
	for (int y = tetris->act_y; y < tetris->curr_len_y; y++)
	{
		for (int x = tetris->act_x; x < tetris->curr_len_x; x++)
		{
			if (tetris->board[y + 1][x] != '0' && tetris->board[y + 1][x] != '1')
				return (0);
		}
	}
	return (1);

}

int				scan_keyboard_state(const Uint8 *state, t_tetris *tetris)
{
	int			direction = 0;

	if (state[SDL_SCANCODE_LEFT])
	{
		if (check_if_tetro_can_move_left(tetris) == 1)
			direction = -1;
	}
	else if (state[SDL_SCANCODE_RIGHT])
	{
		if (check_if_tetro_can_move_right(tetris) == 1)
			direction = 1;
	}
	else if (state[SDL_SCANCODE_DOWN])
	{
		if (check_if_tetro_can_move_down(tetris) == 1)
			direction = 2;
	}
	return (direction);
}

Uint32			scan_exit_and_time(const Uint8 *state, Uint32 currently_pressed)
{
	if (state[SDL_SCANCODE_ESCAPE])
		return (-1);
	if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT] ||
			state[SDL_SCANCODE_DOWN])
		return (SDL_GetTicks());
	return (currently_pressed);
}

Uint32			move_tetro_left_right(t_tetris *tetris, Uint32 currently_pressed,
		Uint32 last_pressed, int direction)
{
	if (currently_pressed > last_pressed + 100)
	{
		if (direction != 2)
			tetris->act_x += direction;
		else if (direction == 2)
			tetris->act_y += 1;
		return (currently_pressed);
	}
	return (last_pressed);
}

void			register_landed_tetro_in_board(t_tetris *tetris)
{
	char		a = 65 + tetris->tetro_type;

	for (int i = tetris->act_y; i < tetris->act_y + tetris->curr_len_y; i++)
	{
		for (int j = tetris->act_x; j < tetris->act_x + tetris->curr_len_x; j++)
		{
			if (tetris->curr_tetro[i - tetris->act_y][j - tetris->act_x] != 0)
				tetris->board[i][j] = a;
		}
	}
}

int				update_tetris_board_state(t_tetris *tetris)
{
	// CLEAR OLD LOCATION
	for (int i = tetris->prev_y; i < tetris->prev_y + tetris->curr_len_y; i++)
	{
		for (int j = tetris->prev_x; j < tetris->prev_x + tetris->curr_len_x; j++)
			tetris->board[i][j] = '0';
	}
	// PLACE NEW LOCATION
	for (int i = tetris->act_y; i < tetris->act_y + tetris->curr_len_y; i++)
	{
		for (int j = tetris->act_x; j < tetris->act_x + tetris->curr_len_x; j++)
		{
			if (tetris->curr_tetro[i - tetris->act_y][j - tetris->act_x] != 0)
				tetris->board[i][j] = '1';
			if (i == 19 || (tetris->board[i][j] == '1' &&
						tetris->board[i + 1][j] != '0'))
			{
				register_landed_tetro_in_board(tetris);
				tetris->spawned = 0;
				print_tetris_board(tetris);
			}
		}
	}
	tetris->prev_y = tetris->act_y;
	tetris->prev_x = tetris->act_x;
	return (tetris->spawned);
}

void			game_loop(t_sdl *sdl, t_tetris *tetris)
{
	Uint32		last_time = 0;
	Uint32		current_time;
	int			direction = 0;
	Uint32		last_pressed = 0;
	Uint32		currently_pressed;
	const Uint8	*state;

	while (tetris->lost != 1)
	{
		direction = 0;
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		current_time = SDL_GetTicks();
		if (tetris->spawned == 0)
			spawn_new_tetro(sdl, tetris);
		if ((currently_pressed =scan_exit_and_time(state,
						currently_pressed)) == (Uint32)-1)
			return ;
		direction = scan_keyboard_state(state, tetris);
		last_pressed = move_tetro_left_right(tetris, currently_pressed,
				last_pressed, direction);
		if (current_time > last_time + 500)
		{
			if (tetris->act_y + tetris->curr_len_y <= 19)
				tetris->act_y += 1;
			last_time = current_time;
		}
		print_tetro_on_screen(sdl, tetris);
		tetris->spawned = update_tetris_board_state(tetris);
		SDL_Delay(1);
	}
}
