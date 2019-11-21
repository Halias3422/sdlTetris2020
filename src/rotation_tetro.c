#include "../includes/tetris.h"

void			abort_new_rotation(t_tetris *tetris, int prev_rotation)
{
	tetris->rotation = prev_rotation;
	if (tetris->rotation == 1)
		get_current_tetro(tetris, tetris->tetro_type);
	else if (tetris->rotation == 2)
		get_current_tetro_2(tetris, tetris->tetro_type);
	else if (tetris->rotation == 3)
		get_current_tetro_3(tetris, tetris->tetro_type);
	else if (tetris->rotation == 4)
		get_current_tetro_4(tetris, tetris->tetro_type);
	tetris->act_x = tetris->prev_x;
	tetris->act_y = tetris->prev_y;
}

int				check_if_rotation_is_doable(t_tetris *tetris)
{
	for (int i = tetris->act_y; i < tetris->act_y + tetris->curr_len_y; i++)
	{
		for (int j = tetris->act_x; j < tetris->act_x + tetris->curr_len_x; j++)
		{
			if (i == 19 || (i>= 0 && i < 20 && j >= 0 && j < 10 &&
			(tetris->curr_tetro[i - tetris->act_y][j - tetris->act_x] == 1 &&
			 tetris->board[i][j] != '0')))
				return (1);
		}
	}
	return (0);
}

void			rotate_tetro_left(t_tetris *tetris)
{
	int			prev_rotation = tetris->rotation;

	tetris->prev_x = tetris->act_x;
	tetris->prev_y = tetris->act_y;
	tetris->old_rotation = tetris->rotation;
	clear_old_tetro_location_on_board(tetris);
	if (tetris->rotation == 1)
		tetris->rotation = 4;
	else
		tetris->rotation -= 1;
	if (tetris->rotation == 1)
		get_current_tetro(tetris, tetris->tetro_type);
	else if (tetris->rotation == 2)
		get_current_tetro_2(tetris, tetris->tetro_type);
	else if (tetris->rotation == 3)
		get_current_tetro_3(tetris, tetris->tetro_type);
	else if (tetris->rotation == 4)
		get_current_tetro_4(tetris, tetris->tetro_type);
	if (check_if_rotation_is_doable(tetris) == 1)
		abort_new_rotation(tetris, prev_rotation);
}

void			rotate_tetro_right(t_tetris *tetris)
{
	int			**old_tetro = tetris->curr_tetro;
	int			prev_rotation = tetris->rotation;

	tetris->prev_x = tetris->act_x;
	tetris->prev_y = tetris->act_y;
	tetris->old_rotation = tetris->rotation;
	clear_old_tetro_location_on_board(tetris);
	if (tetris->rotation == 4)
		tetris->rotation = 1;
	else
		tetris->rotation += 1;
	if (tetris->rotation == 1)
		get_current_tetro(tetris, tetris->tetro_type);
	else if (tetris->rotation == 2)
		get_current_tetro_2(tetris, tetris->tetro_type);
	else if (tetris->rotation == 3)
		get_current_tetro_3(tetris, tetris->tetro_type);
	else if (tetris->rotation == 4)
		get_current_tetro_4(tetris, tetris->tetro_type);
	if (check_if_rotation_is_doable(tetris) == 1)
		abort_new_rotation(tetris, prev_rotation);
	else
		free(old_tetro);
}