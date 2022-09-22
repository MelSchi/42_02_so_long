/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:33:56 by mschiman          #+#    #+#             */
/*   Updated: 2022/03/27 12:07:21 by mschiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../mlx_mac/mlx.h"
# include "../libft/libft.h"

/* Define key codes */
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_UP 126

/* Define tile size */
# define SIZE 50

/* ERROR CODES */
# define WRONG_ARGS_NB 1
# define FILE_NOT_FOUND 2
# define WRONG_FILENAME 3
# define READ_INPUT 4
# define MLX_ERR 5
# define MALLOC_FAIL 6
# define MLX_IMG 7
# define MLX_WIN 8
/* MAP ERROR CODES */
# define INVALID_CHAR 10
# define COLL_EX 11
# define ONE_PL 12
# define WALL_OPEN 13
# define NOT_RECT 14
# define MAP_READ_ERR 15
/* END OF GAME MSG */
# define WIN 16
# define LOOSE 17

typedef struct s_img
{
	void	*ptr;
	int		bits;
	int		size_line;
	int		endian;
	int		height;
	int		width;
	int		pos_x;
	int		pos_y;
}	t_img;

typedef struct s_map
{
	char	*fname;
	int		file_end;
	int		fd_infile;
	int		player;
	int		wall;
	int		space;
	int		collectible;
	int		exit;
	int		enemy;
	int		width;
	int		line_len;
	int		no_of_lines;
	int		last_line;
	char	*line;
	char	**full_map;
	int		line_counter;
}	t_map;

typedef struct s_var
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		step_counter;
	t_img	pl;
	int		pl_pos_h;
	int		pl_pos_v;
	t_img	pl_2;
	int		pl2_pos_h;
	int		pl2_pos_v;
	t_img	nm1;
	int		nm1_pos_h;
	int		nm1_pos_v;
	t_img	nm2;
	int		nm2_pos_h;
	int		nm2_pos_v;
	t_img	wall;
	t_img	empty;
	t_img	coll;
	t_img	ex;
	t_img	emp;
	t_map	map;
	int		i;
	int		j;
	int		k;
	int		str_len;
	int		frame;
}	t_var;

void	init_error_handler(int error_code);
void	map_error(int error_code, t_var *var);
void	error_handler(int error_code, t_var *var);
void	read_map(t_var *var);
int		ft_strlen_del(const char *s, char del);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	ft_strjoin_so_long(t_var *var, char const *s1, char const *s2);
void	get_next_line_solong(t_var *var);
void	check_for_walls(t_var *var);
void	init_img(t_var *var);
int		render_map(t_var *var);
int		my_key_hook(int keycode, t_var *var);
void	move_player(t_var *var, int v, int h);
int		move_enemy(t_var *var);
int		normal_exit(t_var *var, int msg);

#endif
