/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:46:39 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 11:34:42 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	init_img_enemy(t_var *var)
{
	var->nm1.ptr = mlx_xpm_file_to_image(var->mlx_ptr, "./img/nm1.xpm", \
		&var->nm1.height, &var->nm1.width);
	if (var->nm1.ptr == NULL)
		error_handler(MLX_IMG, var);
	var->nm2.ptr = mlx_xpm_file_to_image(var->mlx_ptr, "./img/nm2.xpm", \
		&var->nm2.height, &var->nm2.width);
	if (var->nm2.ptr == NULL)
		error_handler(MLX_IMG, var);
}

void	init_img(t_var *var)
{
	var->pl.ptr = mlx_xpm_file_to_image(var->mlx_ptr, "./img/pl.xpm", \
		&var->pl.height, &var->pl.width);
	if (var->pl.ptr == NULL)
		error_handler(MLX_IMG, var);
	var->pl_2.ptr = mlx_xpm_file_to_image(var->mlx_ptr, "./img/pl_2.xpm", \
		&var->pl.height, &var->pl.width);
	if (var->pl_2.ptr == NULL)
		error_handler(MLX_IMG, var);
	var->wall.ptr = mlx_xpm_file_to_image(var->mlx_ptr, "./img/wall.xpm", \
		&var->wall.height, &var->wall.width);
	if (var->wall.ptr == NULL)
		error_handler(MLX_IMG, var);
	var->coll.ptr = mlx_xpm_file_to_image(var->mlx_ptr, "./img/coll.xpm", \
		&var->coll.height, &var->coll.width);
	if (var->coll.ptr == NULL)
		error_handler(MLX_IMG, var);
	var->ex.ptr = mlx_xpm_file_to_image(var->mlx_ptr, "./img/ex.xpm", \
		&var->ex.height, &var->ex.width);
	if (var->ex.ptr == NULL)
		error_handler(MLX_IMG, var);
	var->emp.ptr = mlx_xpm_file_to_image(var->mlx_ptr, "./img/emp.xpm", \
		&var->emp.height, &var->emp.width);
	if (var->emp.ptr == NULL)
		error_handler(MLX_IMG, var);
	init_img_enemy(var);
}

static void	render_map_first(t_var *var, int v, int h)
{
	if (var->map.full_map[v][h] == '1')
		mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
			var->wall.ptr, (SIZE * h), (SIZE * v));
	if (var->map.full_map[v][h] == '0')
		mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
			var->emp.ptr, (SIZE * h), (SIZE * v));
	if (var->map.full_map[v][h] == 'N')
	{
		mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
			var->nm1.ptr, (SIZE * h), (SIZE * v));
		var->nm1_pos_h = h;
		var->nm1_pos_v = v;
	}
	if (var->map.full_map[v][h] == 'M')
	{
		mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
			var->nm2.ptr, (SIZE * h), (SIZE * v));
		var->nm2_pos_h = h;
		var->nm2_pos_v = v;
	}
	if (var->map.full_map[v][h] == 'C')
		mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
			var->coll.ptr, (SIZE * h), (SIZE * v));
}

static void	render_map_second(t_var *var, int v, int h)
{
	if (var->map.full_map[v][h] == 'P')
	{
		if (rand() % 3 == 1)
			mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
			var->pl_2.ptr, (SIZE * h), (SIZE * v));
		else
			mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
				var->pl.ptr, (SIZE * h), (SIZE * v));
		var->pl_pos_h = h;
		var->pl_pos_v = v;
	}
	if (var->map.full_map[v][h] == 'E')
		mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, \
			var->ex.ptr, (SIZE * h), (SIZE * v));
}

/* Goes through map array and puts images accordingly. */
int	render_map(t_var *var)
{
	int		h;
	int		v;
	char	*step;

	h = 0;
	v = 0;
	while (v < var->map.no_of_lines)
	{
		h = 0;
		while (h < var->map.line_len)
		{
			render_map_first(var, v, h);
			render_map_second(var, v, h);
			h++;
		}
		v++;
	}
	step = ft_itoa(var->step_counter);
	mlx_string_put(var->mlx_ptr, var->win_ptr, 20, 20, 0xFFFFFF, step);
	free(step);
	return (0);
}
