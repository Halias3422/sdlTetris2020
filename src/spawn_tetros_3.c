#include "../includes/tetris.h"

void			S_tetro_spawn_3( t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 1;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 2);
		for (int j = 0; j < 2; j++)
			tetris->curr_tetro[i][j] = 1;
		if (i == 0)
			tetris->curr_tetro[i][1] = 0;
		else if (i == 2)
			tetris->curr_tetro[i][0] = 0;
	}
	tetris->curr_len_x = 2;
	tetris->curr_len_y = 3;
	if ((tetris->old_rotation == 2  || tetris->old_rotation == 4)
			&& tetris->act_x < 9)
		tetris->act_x += 1;
	if (tetris->old_rotation == 2 && tetris->act_y > 0)
		tetris->act_y -= 1;
}

void			I_tetro_spawn_3(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 0;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 4);
	for (int i = 0; i < 4; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 1);
		tetris->curr_tetro[i][0] = 1;
	}
	tetris->curr_len_x = 1;
	tetris->curr_len_y = 4;
	if (tetris->old_rotation == 2 || tetris->old_rotation == 4)
	{
		if (tetris->act_y > 0)
			tetris->act_y -= 1;
		if (tetris->old_rotation == 4 && tetris->act_y > 0)
			tetris->act_y -= 1;
		tetris->act_x += 2;
	}
}

void			J_tetro_spawn_3(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 1;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 2);
		for (int j = 0; j < 2; j++)
		{
			tetris->curr_tetro[i][j] = 1;
			if (i < 2 && j == 0)
				tetris->curr_tetro[i][j] = 0;
		}
	}
	tetris->curr_len_x = 2;
	tetris->curr_len_y = 3;
	if (tetris->old_rotation == 2 && tetris->act_y > 0)
		tetris->act_y -= 1;
}

void			L_tetro_spawn_3(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 1;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 2);
		tetris->curr_tetro[i][0] = 1;
		tetris->curr_tetro[i][1] = 0;
	}
	tetris->curr_tetro[2][1] = 1;
	tetris->curr_len_x = 2;
	tetris->curr_len_y = 3;
	if (tetris->old_rotation == 4 && tetris->act_y > 0)
		tetris->act_y -= 1;
	if ((tetris->old_rotation == 2 || tetris->old_rotation == 4) &&
			tetris->act_x + tetris->offset_right < 9)
		tetris->act_x += 1;
	if (tetris->old_rotation == 4 && tetris->act_y > 0)
		tetris->act_y -= 1;
}

void			T_tetro_spawn_3(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 2;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i < 2; i++)
	tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 3);
	for (int j = 0; j < 3; j++)
	{
		tetris->curr_tetro[0][j] = 1;
		tetris->curr_tetro[1][j] = 0;
	}
	tetris->curr_tetro[1][1] = 1;
	tetris->curr_len_x = 3;
	tetris->curr_len_y = 2;
	if (tetris->old_rotation == 2 && tetris->act_x > 0)
		tetris->act_x -= 1;
	if ((tetris->old_rotation == 2 || tetris->old_rotation == 4) &&
			tetris->act_y + tetris->curr_len_y < 24)
		tetris->act_y += 1;
	if (tetris->old_rotation == 4 && tetris->act_x >= 7)
		tetris->act_x -= 1;
}

void			Z_tetro_spawn_3(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 1;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 2);
		for (int j = 0; j < 2; j++)
			tetris->curr_tetro[i][j] = 1;
		if (i == 0)
			tetris->curr_tetro[i][0] = 0;
		else if (i == 2)
			tetris->curr_tetro[i][1] = 0;
	}
	tetris->curr_len_x = 2;
	tetris->curr_len_y = 3;
	if ((tetris->old_rotation == 2 || tetris->old_rotation == 4) &&
			tetris->act_x + tetris->offset_right < 10)
		tetris->act_x += 1;
	if (tetris->old_rotation == 4 && tetris->act_y > 0)
		tetris->act_y -= 1;
}


void			get_current_tetro_3(t_tetris *tetris, int tetro)
{
	void		(*tetro_pt[7])(t_tetris *);

	tetro_pt[0] = &(S_tetro_spawn_3);
	tetro_pt[1] = &(I_tetro_spawn_3);
	tetro_pt[2] = &(J_tetro_spawn_3);
	tetro_pt[3] = &(L_tetro_spawn_3);
	tetro_pt[5] = &(T_tetro_spawn_3);
	tetro_pt[6] = &(Z_tetro_spawn_3);
	(tetro_pt[tetro])(tetris);
}
