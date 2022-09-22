/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:50:06 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 10:33:35 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* Defines coordinate changes for pl according to key pressed */
int	my_key_hook(int keycode, t_var *var)
{
	if (keycode == KEY_ESC)
		normal_exit(var, 0);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(var, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(var, 1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(var, 0, 1);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(var, -1, 0);
	else
		mlx_string_put(var->mlx_ptr, var->win_ptr, 40, 20, 0x000000, \
				"Push W, A, S, D or the arrow keys (or Esc to leave).");
	return (0);
}

void	move_player(t_var *var, int v, int h)
{
	if (var->map.full_map[var->pl_pos_v + v][var->pl_pos_h + h] == '0'
		|| var->map.full_map[var->pl_pos_v + v][var->pl_pos_h + h] == 'C')
	{
		if (var->map.full_map[var->pl_pos_v + v][var->pl_pos_h + h] == 'C')
			var->map.collectible--;
		var->map.full_map[var->pl_pos_v][var->pl_pos_h] = '0';
		var->map.full_map[var->pl_pos_v + v][var->pl_pos_h + h] = 'P';
		mlx_clear_window(var->mlx_ptr, var->win_ptr);
		render_map(var);
		var->step_counter++;
	}
	else if (var->map.full_map[var->pl_pos_v + v][var->pl_pos_h + h] == 'E')
	{
		if (var->map.collectible == 0)
			normal_exit(var, WIN);
		else
			mlx_string_put(var->mlx_ptr, var->win_ptr, 40, 20, 0x000000, \
				"Collect the items first!");
	}
	else if (var->map.full_map[var->pl_pos_v + v][var->pl_pos_h + h] == 'N')
		normal_exit(var, LOOSE);
}
