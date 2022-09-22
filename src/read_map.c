/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:53:24 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 11:42:43 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* Initialises all the map variables */
static void	set_map_zero(t_var *var)
{
	var->map.player = 0;
	var->map.wall = 0;
	var->map.collectible = 0;
	var->map.space = 0;
	var->map.exit = 0;
	var->map.enemy = 0;
	var->map.line_len = 0;
	var->map.last_line = 0;
	var->map.no_of_lines = 0;
	var->map.width = 0;
	var->map.file_end = 0;
	var->map.line_counter = 0;
	var->str_len = 0;
}

/* Checks for number of collectibles, players and exits. */
static void	map_check(t_var *var)
{
	if (var->map.collectible == 0 || var->map.exit == 0)
		map_error(COLL_EX, var);
	if (var->map.player != 1)
		map_error(ONE_PL, var);
}

/* Counts the number of lines in a file, presuming the last line has no \n*/
static void	count_lines_items(t_var *var)
{
	char	rd_char;

	var->map.fd_infile = open(var->map.fname, O_RDONLY);
	if (var->map.fd_infile <= 0)
		init_error_handler(FILE_NOT_FOUND);
	while (read(var->map.fd_infile, &rd_char, 1) == 1)
	{
		if (rd_char == '\n')
			var->map.no_of_lines++;
		else if (rd_char == 'C')
			var->map.collectible++;
		else if (rd_char == 'E')
			var->map.exit++;
		else if (rd_char == 'P')
			var->map.player++;
		else if (rd_char == 'M' || rd_char == 'N')
			var->map.enemy++;
		else if (rd_char == '1' || rd_char == '0')
			;
		else
			map_error(INVALID_CHAR, var);
	}
	map_check(var);
	close(var->map.fd_infile);
	var->map.no_of_lines++;
}

void	check_for_walls(t_var *var)
{
	int	i;

	i = 0;
	var->map.wall = 0;
	var->map.line_len = ft_strlen_del(var->map.line, '\n');
	if (var->map.line[0] != '1' || var->map.line[var->map.line_len - 1] != '1')
		map_error(WALL_OPEN, var);
	while (i < var->map.line_len)
	{
		if (var->map.line[i] == '1')
			var->map.wall++;
		else if (var->map.line[i] == '0')
			var->map.space++;
		i++;
	}
}

void	read_map(t_var *var)
{
	var->k = 1;
	set_map_zero(var);
	count_lines_items(var);
	var->map.full_map = (char **) calloc(var->map.no_of_lines, sizeof(char *));
	if (var->map.full_map == NULL)
		error_handler(MALLOC_FAIL, var);
	var->map.fd_infile = open(var->map.fname, O_RDONLY);
	while (var->k <= var->map.no_of_lines)
	{
		get_next_line_solong(var);
		if (var->k == 1 || var->k == var->map.no_of_lines)
		{
			if (var->k == 1)
				var->map.width = var->map.line_len;
			if (var->map.space > 0)
				map_error(WALL_OPEN, var);
			if (var->map.wall != var->map.line_len)
				map_error(NOT_RECT, var);
		}
		if (var->map.line_len != var->map.width)
			map_error(NOT_RECT, var);
		var->k++;
		var->map.space = 0;
	}
}
