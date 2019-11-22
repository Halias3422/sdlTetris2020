#include "../includes/tetris.h"

void			spawn_new_tetro(t_tetris *tetris)
{

	check_letters_on_board(tetris);
	tetris->tetro_type = -1;
	srand(time(NULL));
//	tetris->tetro_type = rand() % 7;
	tetris->tetro_type = 5;
	get_current_tetro(tetris, tetris->tetro_type);
	tetris->act_y = 0;
	tetris->act_x =rand() % ((9 - tetris->offset_right) + 1 -
			tetris->offset_left) + tetris->offset_left;
	tetris->spawned = 1;
	tetris->rotation = 1;
	tetris->old_rotation = -1;
	tetris->prev_x = tetris->act_x;
	tetris->prev_y = tetris->act_y;
}

SDL_Texture		*get_current_tetro_texture(t_sdl *sdl, t_tetris *tetris)
{
	if (tetris->rotation == 1)
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
	}
	else if (tetris->rotation == 2)
	{
		switch (tetris->tetro_type)
		{
			case 0:
				return (sdl->tetros->S2);
			case 1:
				return (sdl->tetros->I2);
			case 2:
				return (sdl->tetros->J2);
			case 3:
				return (sdl->tetros->L2);
			case 5:
				return (sdl->tetros->T2);
			case 6:
				return (sdl->tetros->Z2);
		}
	}
	else if (tetris->rotation == 3)
	{
		switch (tetris->tetro_type)
		{
			case 0:
				return (sdl->tetros->S1);
			case 1:
				return (sdl->tetros->I1);
			case 2:
				return (sdl->tetros->J3);
			case 3:
				return (sdl->tetros->L3);
			case 5:
				return (sdl->tetros->T3);
			case 6:
				return (sdl->tetros->Z1);
		}
	}
	else if (tetris->rotation == 4)
	{
		switch (tetris->tetro_type)
		{
			case 0:
				return (sdl->tetros->S2);
			case 1:
				return (sdl->tetros->I2);
			case 2:
				return (sdl->tetros->J4);
			case 3:
				return (sdl->tetros->L4);
			case 5:
				return (sdl->tetros->T4);
			case 6:
				return (sdl->tetros->Z2);
		}
	}
	failure_exit_program("Could Not Retreive Current Tetro Texture", sdl);
	return (NULL);
}

void			render_all_grounded_tetros(t_sdl *sdl, t_tetris *tetris)
{
	int			i = 0;
	SDL_Rect	dst = {sdl->tetro_x,
					   sdl->tetro_y,
					   sdl->tetro_size,
					   sdl->tetro_size};

	while (tetris->board[i])
	{
		int j = 0;
		dst.x = sdl->tetro_x;
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
			dst.x += 64 * sdl->disp_size;
			j++;
		}
		dst.y += sdl->tetro_size;
		i++;
	}
}

void			print_tetro_on_screen(t_sdl *sdl, t_tetris *tetris)
{
	SDL_Rect	playground_dst = {sdl->playground_offset_x,
								  sdl->playground_offset_y,
								  sdl->playground_x,
								  sdl->playground_y};
	SDL_Rect	dst = {sdl->tetro_x + ((tetris->act_x + 1) * (sdl->tetro_size)) - sdl->tetro_size,
					   sdl->tetro_y + ((tetris->act_y + 1) * (sdl->tetro_size)) - sdl->tetro_size,
					   (tetris->curr_len_x * 65) * sdl->disp_size,
					   (tetris->curr_len_y * 65) * sdl->disp_size};

	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_copy(sdl, sdl->renderer, sdl->playground, NULL, &playground_dst);
	SDL_render_copy(sdl, sdl->renderer, get_current_tetro_texture(sdl, tetris),
			NULL, &dst);
	render_all_grounded_tetros(sdl, tetris);
	SDL_RenderPresent(sdl->renderer);
}

int				scan_keyboard_state(const Uint8 *state, t_tetris *tetris)
{
	SDL_Event	event;
	int			check = 0;

	if (state[SDL_SCANCODE_LEFT])
	{
		if (check_if_tetro_can_move_left(tetris) == 1 && check++ == 0)
			tetris->act_x -= 1;
	}
	else if (state[SDL_SCANCODE_RIGHT])
	{
		if (check_if_tetro_can_move_right(tetris) == 1 && check++ == 0)
			tetris->act_x += 1;
	}
	else if (state[SDL_SCANCODE_DOWN])
	{
		if (check_if_tetro_is_grounded(tetris) == 0 && check++ == 0)
			tetris->act_y += 1;
	}
	else if (state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_E])
		check++;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q
				&& tetris->tetro_type != 4)
			check = rotate_tetro_left(tetris);
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e
				&& tetris->tetro_type != 4)
			check = rotate_tetro_right(tetris);
	}
	return (check);
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

void			register_landed_tetro_in_board(t_tetris *tetris)
{
	char		a = 65 + tetris->tetro_type;

	for (int i = tetris->act_y; i < tetris->act_y + tetris->curr_len_y; i++)
	{
		for (int j = tetris->act_x; j < tetris->act_x + tetris->curr_len_x; j++)
		{
			if (i >= 0 && tetris->curr_tetro[i - tetris->act_y][j - tetris->act_x] != 0)
			{
				tetris->board[i][j] = a;
			}
		}
	}
}

void			clear_old_tetro_location_on_board(t_tetris *tetris)
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (tetris->board[y][x] == '1')
				tetris->board[y][x] = '0';
		}
	}
}

int				check_if_tetro_is_grounded(t_tetris *tetris)
{
	for (int i = tetris->act_y; i < tetris->act_y + tetris->curr_len_y; i++)
	{
		for (int j = tetris->act_x; j < tetris->act_x + tetris->curr_len_x; j++)
		{
			if ((i == tetris->act_y && i + tetris->curr_len_y >= 20) ||
			(i>= 0 && (tetris->curr_tetro[i - tetris->act_y][j - tetris->act_x] == 1 &&
			(i - tetris->act_y == tetris->curr_len_y - 1 ||
			tetris->curr_tetro[i - tetris->act_y + 1][j - tetris->act_x] == 0) &&
			tetris->board[i + 1][j] != '0')))
				return (1);
		}
	}
	return (0);
}

void			update_board_with_new_location(t_tetris *tetris)
{
	for (int y = tetris->act_y; y < tetris->act_y + tetris->curr_len_y; y++)
	{
		for (int x = tetris->act_x; x < tetris->act_x + tetris->curr_len_x; x++)
		{
			if (tetris->curr_tetro[y - tetris->act_y][x - tetris->act_x] == 1)
				tetris->board[y][x] = '1';
		}
	}
}

void			game_loop(t_sdl *sdl, t_tetris *tetris)
{
	Uint32		last_turn = SDL_GetTicks();
	Uint32		last_moved = 0;
	Uint32		current_time;
	int			last_stand = 0;
	const Uint8	*state;

	while (tetris->lost != 1)
	{
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		current_time = SDL_GetTicks();
		if (tetris->spawned == 0)
			spawn_new_tetro(tetris);
		tetris->prev_x = tetris->act_x;
		tetris->prev_y = tetris->act_y;
		if (state[SDL_SCANCODE_ESCAPE])
			return ;
		if (current_time > last_moved + 100 && scan_keyboard_state(state, tetris) > 0)
			last_moved = SDL_GetTicks();
		if (current_time > last_turn + 500)
		{
			if (check_if_tetro_is_grounded(tetris) == 0)
				tetris->act_y += 1;
			last_turn = current_time;
		}
		clear_old_tetro_location_on_board(tetris);
		print_tetro_on_screen(sdl, tetris);
		if (check_if_tetro_is_grounded(tetris) == 0)
			last_stand = 0;
		else if (last_stand == 0 && check_if_tetro_is_grounded(tetris) == 1)
			last_stand = 1;
		else if (check_if_tetro_is_grounded(tetris) == 1 && last_stand == 1 &&
				current_time > last_moved + 500)
			last_stand = 2;
		update_board_with_new_location(tetris);
		if (last_stand == 2)
		{
			register_landed_tetro_in_board(tetris);
			print_tetris_board(tetris);
			tetris->spawned = 0;
			last_stand = 0;
		}
		SDL_Delay(1);
	}
}

/*
void			game_loop(t_sdl *sdl, t_tetris *tetris)
{
	Uint32		last_time = 0;
	Uint32		current_time;
	int			direction = 0;
	Uint32		last_pressed = 0;
	Uint32		currently_pressed = SDL_GetTicks();
	int			last_stand = 0;
	const Uint8	*state;

	while (tetris->lost != 1)
	{
		direction = 0;
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		current_time = SDL_GetTicks();
		if (tetris->spawned == 0)
			spawn_new_tetro(tetris);
		if ((currently_pressed = scan_exit_and_time(state,
						currently_pressed)) == (Uint32)-1)
			return ;
		direction = scan_keyboard_state(state, tetris);
		last_pressed = move_tetro_left_right(tetris, currently_pressed,
				last_pressed, direction, current_time, &last_stand);
		if (current_time > last_time + 500)
		{
			if (tetris->act_y + tetris->curr_len_y < 20 && check_if_tetro_is_grounded(tetris) == 0)
				tetris->act_y += 1;
			printf("ICI tetris->act_y = %d\n", tetris->act_y);
			last_time = current_time;
		}
		clear_old_tetro_location_on_board(tetris);
		tetris->prev_x = tetris->act_x;
		tetris->prev_y = tetris->act_y;
		update_board_with_new_location(tetris);
		if (check_if_tetro_is_grounded(tetris) == 1 && last_stand == 0)
		{
			printf("last stand a 1\n");
			last_stand = 1;
		}
		if (check_if_tetro_is_grounded(tetris) == 0)
		{
			if (last_stand == 1)
				last_stand = 0;
		}
		print_tetro_on_screen(sdl, tetris);
		if (last_stand == 2)
		{
			printf("last stand a 2\n");
			register_landed_tetro_in_board(tetris);
			print_tetris_board(tetris);
			tetris->spawned = 0;
			last_stand = 0;
		}
		SDL_Delay(1);
	}
}
*/
