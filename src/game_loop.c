#include "../includes/tetris.h"

int				check_if_tetro_type_already_in_list(int tetro_type, t_spawning *next_tetro)
{
	t_spawning	*tmp = next_tetro;

	while (tmp->next)
	{
		if (tmp->tetro_type == tetro_type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void			spawn_new_tetro(t_tetris *tetris)
{
	t_spawning	*head = tetris->next_tetro;
	int			tmp_stored = 0;

	if (tetris->stored_tetro_type != -1 && tetris->retreive_stored_tetro == 1)
	{
		tmp_stored = tetris->tetro_type;
		tetris->tetro_type = tetris->stored_tetro_type;
		tetris->stored_tetro_type = tmp_stored;
		tetris->retreive_stored_tetro = 0;
	}
	else
	{
		tetris->tetro_type = tetris->next_tetro->tetro_type;
		while (tetris->next_tetro->next != NULL)
		{
			tetris->next_tetro->tetro_type = tetris->next_tetro->next->tetro_type;
			tetris->next_tetro = tetris->next_tetro->next;
		}
		tetris->next_tetro->tetro_type = rand() % 7;
		while (check_if_tetro_type_already_in_list(tetris->next_tetro->tetro_type, head) == 1)
			tetris->next_tetro->tetro_type = rand() % 7;
		tetris->next_tetro = head;
	}
	get_current_tetro(tetris, tetris->tetro_type);
	tetris->act_y = 4 - tetris->curr_len_y;
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
					   sdl->tetro_y - (4 * sdl->tetro_size),
					   sdl->tetro_size,
					   sdl->tetro_size};

	while (i < 24 && tetris->board[i])
	{
		int j = 0;
		dst.x = sdl->tetro_x;
		while (j < 10 && i < 24 && tetris->board[i][j])
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
			else if (tetris->board[i][j] == 'W')
				SDL_render_copy(sdl, sdl->renderer, sdl->tiles->white, NULL, &dst);
			dst.x += 64 * sdl->disp_size;
			j++;
		}
		dst.y += sdl->tetro_size;
		i++;
	}
}

void			get_current_tetro_with_correct_rotation(t_tetris *tetris,
				int tetro_type)
{
	if (tetris->rotation == 1)
		get_current_tetro(tetris, tetro_type);
	else if (tetris->rotation == 2)
		get_current_tetro_2(tetris, tetro_type);
	else if (tetris->rotation == 3)
		get_current_tetro_3(tetris, tetro_type);
	else if (tetris->rotation == 4)
		get_current_tetro_4(tetris, tetro_type);
}

void			clean_stored_struct(t_tetris *stored)
{
	for (int i = 0; i < stored->curr_len_y; i++)
		free(stored->curr_tetro[i]);
	free(stored->curr_tetro);
	free(stored);
}

void			print_stored_tetro_window(t_sdl *sdl, t_tetris *tetris)
{
	SDL_Rect	dst = {sdl->playground_offset_x - 32 - (320 * sdl->disp_size),
					   sdl->playground_offset_y * 2,
					   320 * sdl->disp_size,
					   368 * sdl->disp_size};
	SDL_Rect	tetro_dst = {0, 0, 0, 0};

	SDL_render_copy(sdl, sdl->renderer, sdl->stored_tetro, NULL, &dst);
	if (tetris->stored_tetro_type == -1)
		return ;
	sdl->stored = (t_tetris*)malloc(sizeof(t_tetris));
	sdl->stored->tetro_type = tetris->stored_tetro_type;
	sdl->stored->rotation = 1;
	get_current_tetro(sdl->stored, sdl->stored->tetro_type);
	tetro_dst.x = (sdl->playground_offset_x - 32 - (320 * sdl->disp_size)) +
		(32 *sdl->disp_size) +  (((256 * sdl->disp_size) -
		(sdl->stored->curr_len_x * (64 * sdl->disp_size))) / 2);
	tetro_dst.y = (sdl->playground_offset_y * 2) + (80 * sdl->disp_size) +
		(((256 * sdl->disp_size) - (sdl->stored->curr_len_y * (64 * sdl->disp_size))) / 2);
	tetro_dst.h = (64 * sdl->disp_size) * sdl->stored->curr_len_y;
	tetro_dst.w = (64 * sdl->disp_size) * sdl->stored->curr_len_x;
	SDL_render_copy(sdl, sdl->renderer, get_current_tetro_texture(sdl, sdl->stored),
			NULL, &tetro_dst);
	clean_stored_struct(sdl->stored);
}

void			print_next_tetros_window(t_sdl *sdl, t_tetris *tetris)
{
	t_spawning	*tmp = tetris->next_tetro;
	int			tetro_offset = 0;
	SDL_Rect	dst = {sdl->playground_offset_x + 32 + sdl->playground_x,
					   sdl->playground_offset_y * 2,
					   320 * sdl->disp_size,
					   912 * sdl->disp_size};
	SDL_Rect	tetro_dst = {0, 0, 0, 0};

	SDL_render_copy(sdl, sdl->renderer, sdl->next_tetro, NULL, &dst);
	while (tmp->next)
	{
		sdl->next_t = (t_tetris*)malloc(sizeof(t_tetris));
		sdl->next_t->tetro_type = tmp->tetro_type;
		sdl->next_t->rotation = 1;
		get_current_tetro(sdl->next_t, sdl->next_t->tetro_type);
		tetro_dst.x = (sdl->playground_offset_x + 32 + sdl->playground_x) + (32 * sdl->disp_size) + (((256 * sdl->disp_size) - (sdl->next_t->curr_len_x * (64 * sdl->disp_size))) / 2);
		tetro_dst.y = (sdl->playground_offset_y * 2) + (tetro_offset * (272 * sdl->disp_size)) + (80 * sdl->disp_size) + (((256 * sdl->disp_size) - (sdl->next_t->curr_len_y * (64 * sdl->disp_size))) / 2);
		tetro_dst.h = (64 * sdl->disp_size) * sdl->next_t->curr_len_y;
		tetro_dst.w = (64 * sdl->disp_size) * sdl->next_t->curr_len_x;
		SDL_render_copy(sdl, sdl->renderer, get_current_tetro_texture(sdl, sdl->next_t),
				NULL, &tetro_dst);
		 tetro_offset += 1;
		 tmp = tmp->next;
	}
	clean_stored_struct(sdl->next_t);

}

void			render_ghost_tetro(t_sdl *sdl, t_tetris *tetris)
{
	SDL_Texture	*ghost;
	int			real_act_y = tetris->act_y;
	SDL_Rect	dst = {sdl->tetro_x + ((tetris->act_x + 1) * (sdl->tetro_size)) - sdl->tetro_size,
					   sdl->tetro_y + (((tetris->act_y - 4) + 1) * (sdl->tetro_size)) - sdl->tetro_size,
					   (tetris->curr_len_x * 65) * sdl->disp_size,
					   (tetris->curr_len_y * 65) * sdl->disp_size};
	SDL_Rect	src = {0,
					   0,
					   (tetris->curr_len_x * 65),
					   (tetris->curr_len_y * 65)};
	int			tmp_curr_len_y = tetris->curr_len_y;

	ghost = get_current_tetro_texture(sdl, tetris);
	if (SDL_SetTextureAlphaMod(ghost, 60) != 0)
		failure_exit_program("Change Opacity Of Ghost Texture", sdl);
	while (check_if_tetro_is_grounded(tetris) != 1)
		tetris->act_y += 1;
	dst.y = sdl->tetro_y + (((tetris->act_y - 4) + 1) * (sdl->tetro_size)) - sdl->tetro_size;
	if (tetris->act_y < 4)
	{
		tmp_curr_len_y = tetris->act_y;
		while (tmp_curr_len_y++ < 4)
		{
			src.y += 65;
			dst.y += 65 * sdl->disp_size;
			dst.h -= 65 * sdl->disp_size;
		}
	}
	SDL_render_copy(sdl, sdl->renderer, ghost, NULL, &dst);
	tetris->act_y = real_act_y;
	if (SDL_SetTextureAlphaMod(ghost, 255) != 0)
		failure_exit_program("Restauring Transparency of ghost", sdl);
}

void			print_tetro_on_screen(t_sdl *sdl, t_tetris *tetris)
{
	SDL_Rect	playground_dst = {sdl->playground_offset_x,
								  sdl->playground_offset_y,
								  sdl->playground_x,
								  sdl->playground_y};
	SDL_Rect	dst = {sdl->tetro_x + ((tetris->act_x + 1) * (sdl->tetro_size)) - sdl->tetro_size,
					   sdl->tetro_y + (((tetris->act_y - 4) + 1) * (sdl->tetro_size)) - sdl->tetro_size,
					   (tetris->curr_len_x * 65) * sdl->disp_size,
					   (tetris->curr_len_y * 65) * sdl->disp_size};
	SDL_Rect	src = {0,
					   0,
					   (tetris->curr_len_x * 65),
					   (tetris->curr_len_y * 65)};
	int			tmp_curr_len_y = tetris->curr_len_y;

	if (tetris->act_y < 4)
	{
		tmp_curr_len_y = tetris->act_y;
		while (tmp_curr_len_y++ < 4)
		{
			src.y += 65;
			dst.y += 65 * sdl->disp_size;
			dst.h -= 65 * sdl->disp_size;
		}
	}
	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_copy(sdl, sdl->renderer, sdl->playground, NULL, &playground_dst);
	if (tetris->spawned == 1)
		SDL_render_copy(sdl, sdl->renderer, get_current_tetro_texture(sdl, tetris),
				&src, &dst);
	render_all_grounded_tetros(sdl, tetris);
	if (tetris->spawned == 1)
		render_ghost_tetro(sdl, tetris);
	print_stored_tetro_window(sdl, tetris);
	print_next_tetros_window(sdl, tetris);
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
	if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_q && tetris->tetro_type != 4)
			check = rotate_tetro_left(tetris);
		else if (event.key.keysym.sym == SDLK_e && tetris->tetro_type != 4)
			check = rotate_tetro_right(tetris);
		else if (event.key.keysym.sym == SDLK_SPACE)
		{
			while (check_if_tetro_is_grounded(tetris) != 1)
				tetris->act_y += 1;
		}
		else if (event.key.keysym.sym == SDLK_s && tetris->has_stored == 0)
		{
			if (tetris->stored_tetro_type == -1)
			{
				tetris->stored_tetro_type = tetris->tetro_type;
				clear_old_tetro_location_on_board(tetris);
			}
			else
				tetris->retreive_stored_tetro = 1;
			tetris->spawned = 0;
			tetris->has_stored = 1;
		}
		else if (event.key.keysym.sym == SDLK_g && tetris->stored_tetro_type != -1)
		{
			tetris->spawned = 0;
			tetris->retreive_stored_tetro = 1;
		}
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

int				register_landed_tetro_in_board(t_tetris *tetris)
{
	char		a = 65 + tetris->tetro_type;

	if (tetris->act_y < 4)
		return (1);
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
	return (0);
}

void			clear_old_tetro_location_on_board(t_tetris *tetris)
{
	for (int y = 0; y < 24; y++)
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
			if ((i == tetris->act_y && i + tetris->curr_len_y >= 24) ||
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
		if (current_time > last_moved + 70 && scan_keyboard_state(state, tetris) > 0)
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
			//NEED TO REORDER TO NOT LOOSE IF CLEARED LINE
			tetris->spawned = 0;
			tetris->has_stored = 0;
			tetris->lost = register_landed_tetro_in_board(tetris);
			check_for_full_lines(sdl, tetris);
			last_stand = 0;
		}
		SDL_Delay(1);
	}
	printf("YOU LOST YOU FUCKING LOOOOOOOOOOSER\n");
	SDL_Delay(500);
}
