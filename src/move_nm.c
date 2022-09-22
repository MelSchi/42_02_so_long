/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 10:25:22 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 10:59:47 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	enemy_moves(int move, int *v_ptr, int *h_ptr)
{
	if (move == 0)
	{
		*v_ptr = 0;
		*h_ptr = -1;
	}
	else if (move == 1)
	{
		*v_ptr = 1;
		*h_ptr = 0;
	}
	else if (move == 2)
	{
		*v_ptr = 0;
		*h_ptr = 1;
	}
	else if (move == 3)
	{
		*v_ptr = -1;
		*h_ptr = 0;
	}
}

static void	move_first_enemy(t_var *var, int v, int h)
{
	if (var->map.full_map[var->nm1_pos_v + v][var->nm1_pos_h + h] == '0')
	{
		var->map.full_map[var->nm1_pos_v][var->nm1_pos_h] = '0';
		var->map.full_map[var->nm1_pos_v + v][var->nm1_pos_h + h] = 'N';
		mlx_clear_window(var->mlx_ptr, var->win_ptr);
		render_map(var);
	}
	else if (var->map.full_map[var->nm1_pos_v + v][var->nm1_pos_h + h] == 'P')
	{
		var->map.full_map[var->nm1_pos_v][var->nm1_pos_h] = '0';
		var->map.full_map[var->nm1_pos_v + v][var->nm1_pos_h + h] = 'N';
		mlx_clear_window(var->mlx_ptr, var->win_ptr);
		render_map(var);
		normal_exit(var, LOOSE);
	}
}

static void	move_second_enemy(t_var *var, int v, int h)
{
	if (var->map.full_map[var->nm2_pos_v + v][var->nm2_pos_h + h] == '0')
	{
		var->map.full_map[var->nm2_pos_v][var->nm2_pos_h] = '0';
		var->map.full_map[var->nm2_pos_v + v][var->nm2_pos_h + h] = 'M';
		mlx_clear_window(var->mlx_ptr, var->win_ptr);
		render_map(var);
	}
	else if (var->map.full_map[var->nm2_pos_v + v][var->nm2_pos_h + h] == 'P')
	{
		var->map.full_map[var->nm2_pos_v][var->nm2_pos_h] = '0';
		var->map.full_map[var->nm2_pos_v + v][var->nm2_pos_h + h] = 'N';
		mlx_clear_window(var->mlx_ptr, var->win_ptr);
		render_map(var);
		normal_exit(var, LOOSE);
	}
}

int	move_enemy(t_var *var)
{
	int	v;
	int	h;
	int	*v_ptr;
	int	*h_ptr;

	v = 0;
	h = 0;
	v_ptr = &v;
	h_ptr = &h;
	var->frame++;
	if (var->frame == 5000)
	{
		enemy_moves(rand() % 4, v_ptr, h_ptr);
		move_first_enemy(var, v, h);
		if (var->map.enemy == 2)
		{
			enemy_moves(rand() % 4, v_ptr, h_ptr);
			move_second_enemy(var, v, h);
		}
		var->frame = 0;
	}
	return (0);
}
