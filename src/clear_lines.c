#include "../includes/tetris.h"

void			display_cleared_lines(t_sdl *sdl, t_tetris *tetris,
				int *cleared_lines, int nb_cleared)
{
	// REGISTER FULL LINES ON BOARD
	for (int i = 0; i <= nb_cleared; i++)
	{
		for (int x = 0; x < 10; x++)
			tetris->board[cleared_lines[i]][x] = 'W';
	}
	print_tetro_on_screen(sdl, tetris);
	SDL_Delay(150);
	// REMOVE FULL LINES FROM BOARD
	for (int j = 0; j <= nb_cleared; j++)
	{
		for (int y = cleared_lines[j]; y > 0; y--)
		{
			for (int x = 0; x < 10; x++)
				tetris->board[y][x] = tetris->board[y - 1][x];
		}
	}
}

void			check_for_full_lines(t_sdl *sdl, t_tetris *tetris)
{
	int			cleared_lines[4] = {-1, -1, -1, -1};
	int			nb_cleared = -1;

	for (int y = 4; y < 24; y++)
	{
		int check = 0;
		for (int x = 0; x < 10; x++)
		{
			if (tetris->board[y][x] != '0' && tetris->board[y][x] != '1')
				check++;
		}
		if (check == 10)
			cleared_lines[++nb_cleared] = y;
	}
	if (nb_cleared > -1)
	{
		display_cleared_lines(sdl, tetris, cleared_lines, nb_cleared);
		tetris->score += 100 + ((200 * nb_cleared) * (0.5 * nb_cleared));
		printf("tetris->score = %d\n", tetris->score);
	}
}
