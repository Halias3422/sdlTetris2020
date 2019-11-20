#include "../includes/tetris.h"

int			check_if_tetro_can_move_left(t_tetris *tetris)
{
	if (tetris->act_x - tetris->offset_left - 1 < 0)
		return (0);
	for (int y = tetris->act_y; y < tetris->act_y + tetris->curr_len_y; y++)
	{
		for (int x = tetris->act_x; x < tetris->act_x + tetris->curr_len_x; x++)
		{
			if (y >= 0 && tetris->board[y][x - 1] != '0' && tetris->board[y][x - 1] != '1')
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
			if (y >= 0 && tetris->board[y][x + 1] != '0' && tetris->board[y][x + 1] != '1')
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
			if (y >= 0 && tetris->board[y + 1][x] != '0' && tetris->board[y + 1][x] != '1')
				return (0);
		}
	}
	return (1);

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
