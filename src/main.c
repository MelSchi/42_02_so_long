/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:24:38 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 11:36:41 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* A map is built as follows: */
/* 0 for an empty space, 1 for a wall, C for a collectible, E for a map exit, */
/* P for the player’s starting position and if you like add N for an enemy */
/* and M for a second enemy. Walls must be closed, map must be rectangular */
/* and you need at least one P, one E and two Cs. Have fun! */

static void	check_filename(t_var *var, char **argv)
{
	int		len;

	len = 0;
	var->map.fname = argv[1];
	len = ft_strlen(var->map.fname);
	if (!(var->map.fname[len - 1] == 'r' && var->map.fname[len - 2] == 'e') \
		|| !(var->map.fname[len - 3] == 'b' && var->map.fname[len - 4] == '.'))
		init_error_handler(WRONG_FILENAME);
}

int	main(int argc, char **argv)
{
	t_var	var;

	var.frame = 0;
	var.step_counter = 0;
	if (argc != 2)
		init_error_handler(WRONG_ARGS_NB);
	check_filename(&var, argv);
	read_map(&var);
	var.mlx_ptr = mlx_init();
	if (var.mlx_ptr == NULL)
		init_error_handler(MLX_ERR);
	init_img(&var);
	var.win_ptr = mlx_new_window(var.mlx_ptr, (var.map.line_len * SIZE), \
		(var.map.no_of_lines * SIZE), "42 WOB Game");
	if (var.win_ptr == NULL)
		error_handler(MLX_WIN, &var);
	render_map(&var);
	mlx_hook(var.win_ptr, 17, 0, normal_exit, &var);
	mlx_key_hook(var.win_ptr, *my_key_hook, &var);
	if (var.map.enemy > 0)
		mlx_loop_hook(var.mlx_ptr, *move_enemy, &var);
	mlx_loop(var.mlx_ptr);
	return (0);
}
