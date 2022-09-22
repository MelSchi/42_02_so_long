/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_so_long.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:09:09 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 11:11:14 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	get_next_line_solong(t_var *var)
{
	char	rd_char[2];
	int		found_nl;

	found_nl = 0;
	var->map.line = NULL;
	ft_bzero(rd_char, 2);
	while (found_nl == 0)
	{
		if ((read(var->map.fd_infile, &rd_char[0], 1)) != 1)
		{
			var->map.last_line = 1;
			break ;
		}
		if (rd_char[0] == '\n')
			found_nl = 1;
		var->map.line = ft_strjoin_gnl(var->map.line, rd_char);
	}
	var->map.file_end = 1;
	var->map.line = ft_strjoin_gnl(var->map.line, "\n");
	var->map.line_len = ft_strlen_del(var->map.line, '\n');
	check_for_walls(var);
	var->map.full_map[var->map.line_counter] = ft_strdup(var->map.line);
	var->map.line_counter++;
	free(var->map.line);
}
