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

void			check_letters_on_board(t_tetris *tetris)
{
	int			i = 0;
	int			a = 0;
	int			b = 0;
	int			c = 0;
	int			d = 0;
	int			e = 0;
	int			f = 0;
	int			g = 0;

	while (tetris->board[i])
	{
		int j = 0;
		while (tetris->board[i][j])
		{
			if (tetris->board[i][j] == 'B')
				b++;
			else if (tetris->board[i][j] == 'C')
				c++;
			else if (tetris->board[i][j] == 'A')
				a++;
			else if (tetris->board[i][j] == 'D')
				d++;
			else if (tetris->board[i][j] == 'F')
				f++;
			else if (tetris->board[i][j] == 'G')
				g++;
			else if (tetris->board[i][j] == 'E')
				e++;
			j++;
		}
		i++;
	}
}
