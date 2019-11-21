#include "../includes/tetris.h"

void			S_tetro_spawn_4(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 2;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i < 2; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 3);
		for (int j = 0; j < 3; j++)
			tetris->curr_tetro[i][j] = 1;
	}
	tetris->curr_tetro[0][0] = 0;
	tetris->curr_tetro[1][2] = 0;
	tetris->curr_len_x = 3;
	tetris->curr_len_y = 2;
	if (tetris->old_rotation == 3 && tetris->act_x > 0)
		tetris->act_x -= 1;
	while (tetris->act_x + tetris->offset_right > 9)
			tetris->act_x--;
}

void			I_tetro_spawn_4(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 3;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 1);
	tetris->curr_tetro[0] = (int*)malloc(sizeof(int) * 4);
	for (int i = 0; i < 4; i++)
		tetris->curr_tetro[0][i] = 1;
	tetris->curr_len_x = 4;
	tetris->curr_len_y = 1;
	if (tetris->old_rotation == 1 || tetris->old_rotation == 3)
	{
		if (tetris->act_y + tetris->curr_len_y < 20)
		tetris->act_y += 2;
		if (tetris->act_x == 1)
			tetris->act_x -= 1;
		if (tetris->act_x > 1 && tetris->act_x <= 8)
			tetris->act_x -= 2;
		else if (tetris->act_x == 9)
			tetris->act_x -= 3;
	}
}

void			J_tetro_spawn_4(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 2;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 2);
	for (int j = 0; j < 2; j++)
		tetris->curr_tetro[j] = (int*)malloc(sizeof(int) * 3);
	for (int i = 0; i < 3; i++)
	{
		tetris->curr_tetro[0][i] = 0;
		tetris->curr_tetro[1][i] = 1;
	}
	tetris->curr_tetro[0][0] = 1;
	tetris->curr_len_x = 3;
	tetris->curr_len_y = 2;
	if (tetris->old_rotation == 1 && tetris->act_x > 0)
		tetris->act_x -= 1;
}

void			L_tetro_spawn_4(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 2;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i < 2; i++)
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 3);
	for (int j = 0; j < 3; j++)
			tetris->curr_tetro[0][j] = 1;
	for (int k = 0;k < 3; k++)
			tetris->curr_tetro[1][k] = 0;
	tetris->curr_tetro[1][0] = 1;
	tetris->curr_len_x = 3;
	tetris->curr_len_y = 2;
	if ((tetris->old_rotation == 3 || tetris->old_rotation == 1) &&
		tetris->act_y + tetris->curr_len_y < 20)
		tetris->act_y += 1;
	if (tetris->old_rotation == 3 && tetris->act_x > 0)
		tetris->act_x -= 1;
	if (tetris->act_x >= 8)
		tetris->act_x -= 1;
}

void			T_tetro_spawn_4(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 1;
	tetris->curr_tetro = (int**)malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 2);
		tetris->curr_tetro[i][0] = 0;
		tetris->curr_tetro[i][1] = 1;
	}
	tetris->curr_tetro[1][0] = 1;
	tetris->curr_len_x = 2;
	tetris->curr_len_y = 3;
	if (tetris->old_rotation == 3 && tetris->act_y > 0)
		tetris->act_y -= 1;
}

void			Z_tetro_spawn_4(t_tetris *tetris)
{
	tetris->offset_left = 0;
	tetris->offset_right = 2;
	tetris->curr_tetro = (int**)malloc(sizeof(int*)  * 2);
	for (int i = 0; i < 2; i++)
	{
		tetris->curr_tetro[i] = (int*)malloc(sizeof(int) * 3);
		for (int j = 0; j < 3; j++)
			tetris->curr_tetro[i][j] = 1;
	}
	tetris->curr_tetro[0][2] = 0;
	tetris->curr_tetro[1][0] = 0;
	tetris->curr_len_x = 3;
	tetris->curr_len_y = 2;
	if (tetris->old_rotation == 3 && tetris->act_x > 0)
		tetris->act_x -= 1;
	if ((tetris->old_rotation == 3 || tetris->old_rotation == 1) &&
			tetris->act_y + tetris->curr_len_y < 20)
		tetris->act_y += 1;
}


void			get_current_tetro_4(t_tetris *tetris, int tetro)
{
	void		(*tetro_pt[7])(t_tetris *);

	tetro_pt[0] = &(S_tetro_spawn_4);
	tetro_pt[1] = &(I_tetro_spawn_4);
	tetro_pt[2] = &(J_tetro_spawn_4);
	tetro_pt[3] = &(L_tetro_spawn_4);
	tetro_pt[5] = &(T_tetro_spawn_4);
	tetro_pt[6] = &(Z_tetro_spawn_4);
	(tetro_pt[tetro])(tetris);
}
