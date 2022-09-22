/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:48:25 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 12:09:10 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	early_exit(t_var *var)
{
	int	i;

	i = 0;
	close(var->map.fd_infile);
	while (i < var->map.line_counter)
	{
		free(var->map.full_map[i]);
		i++;
	}
	free(var->map.full_map);
	exit(0);
}

int	normal_exit(t_var *var, int msg)
{
	int	i;

	i = 0;
	if (msg == WIN)
		write(1, "You win!!!\n", 12);
	if (msg == LOOSE)
		write(1, "You lost! Don't let them catch you!\n", 36);
	mlx_destroy_window(var->mlx_ptr, var->win_ptr);
	close(var->map.fd_infile);
	while (i < var->map.line_counter)
	{
		free(var->map.full_map[i]);
		i++;
	}
	free(var->map.full_map);
	exit(0);
}

void	init_error_handler(int error_code)
{
	if (error_code == WRONG_ARGS_NB)
		write(1, "Wrong number of arguments in function call.\n", 45);
	else if (error_code == MLX_ERR)
		write(1, "Unable to initialise mlx.\n", 27);
	else if (error_code == WRONG_FILENAME)
		write(1, "Input file is not .ber\n", 24);
	else if (error_code == READ_INPUT)
		write(1, "Error while reading from input file.\n", 38);
	else if (error_code == MALLOC_FAIL)
		write(1, "Memory allocation failed.\n", 27);
	exit (-1);
}

void	map_error(int error_code, t_var *var)
{
	write(1, "Map is not a valid map.\n", 25);
	if (error_code == WALL_OPEN)
		write(1, "Wall is not closed.\n", 21);
	else if (error_code == NOT_RECT)
		write(1, "Map is not rectangular.\n", 25);
	else if (error_code == COLL_EX)
		write(1, "You need at least 1 collectible and 1 exit.\n", 45);
	else if (error_code == ONE_PL)
		write(1, "Single player game. Reduce to one or add one.\n", 47);
	else if (error_code == INVALID_CHAR)
	{
		write(1, "Your map contains invalid characters.\n", 39);
		write(1, "You can only use 1, 0, P, C, E, M, N.\n", 39);
	}
	early_exit(var);
}

void	error_handler(int error_code, t_var *var)
{
	if (error_code == MLX_IMG)
		write(1, "Error while reading from image file.\n", 38);
	else if (error_code == MLX_WIN)
		write(1, "Error while opening game window.\n", 34);
	else if (error_code == MAP_READ_ERR)
		write(1, "Error while reading from map.\n", 27);
	early_exit(var);
}
