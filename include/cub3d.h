/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarles <rcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:57:47 by rcarles           #+#    #+#             */
/*   Updated: 2022/07/18 21:28:35 by rcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <X11/X.h>
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"

# define W_HEIGHT 768
# define W_WIDTH 1024

# define TRANSLATION_STEP_SIZE 0.1
# define ROTATION_STEP_SIZE 0.08

# define MINIMAP_HEIGHT 280
# define MINIMAP_WIDTH 240

# define MEM_ERR -42

# define ESCAPE 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

# define _RED_   "\e[1;31m"
# define _RST_    "\e[0m"

typedef enum e_orientation
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_orientation;

typedef unsigned int	t_color;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_l;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	*frame;
	t_img	*frame2;

}	t_mlx;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_upoint
{
	size_t	x;
	size_t	y;
}	t_upoint;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	delta_dist;
	t_vector	dist;
	t_vector	step;
	t_point		pos;		
	double		wall_dist;
	int			hit_side;
	int			x_camera;
	int			x_for_tex;
}	t_ray;

typedef struct s_map
{
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	t_vector	spawn_direction;
	t_vector	spawn_position;
	t_vector	spawn_plane;
	t_color		ceiling_color;
	t_color		floor_color;
	size_t		max_x;
	size_t		max_y;
	char		**map;
}	t_map;

typedef struct s_texture
{
	t_img	frame;
	int		width;
	int		height;
}	t_texture;

typedef struct s_slice
{
	double	step;
	double	tex_pos;
	double	x_wall_offset;
	int		x_tex_offset;
	int		y_tex_offset;
	int		height;
	int		draw_start;
	int		draw_end;
}	t_slice;

typedef struct s_key
{
	bool	up;	
	bool	down;	
	bool	rot_right;	
	bool	rot_left;	
	bool	right;	
	bool	left;	
}	t_key;

typedef struct s_game
{
	t_mlx		*mlx;
	t_vector	player;
	t_vector	dir;
	t_vector	plane;
	char		**map;
	t_map		*map_info;
	int			pixel_per_block;
	t_texture	*textures;
	t_key		press;
}	t_game;

/* parsing_utils.c */

void	clean_gnl(int fd);
char	*strip_newline(char *str);
int		str_is_numeric(char *str);
void	remove_newlines(t_map *map);
int		map_params_complete(t_map *map);

/* parsing_bis.c */

int		fill_map(t_map *map, int fd);
int		get_spawn_direction(t_map *map);
int		get_map_size(t_map *map, int fd, char *first_line);
int		is_map_valid(char **map, size_t max_x, size_t max_y);

/* parsing.c */

int		parse_map_file(t_map *map, char *path);

/* hooks.c */

int		render(t_game *game);
int		window_cross(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
int		mouse_move(int x, int y, t_game *game);

/* utils.c */

void	free_map(t_map map);
void	free_tab(char **tab);
int		destroy_mlx(t_mlx *mlx);
int		str_ends_with(char *str, char *end);
size_t	count_char_in_str(char *str, char c);

/* raycasting.c */

void	raycasting(t_game *game);

/* movement.c */

void	rotate(t_game *game, double rot_speed);
void	translate(t_game *game, double dir_step, double plane_step);

/* drawing.c */

void	draw_line(t_img *frame, t_point p1, t_point p2, int color);
void	draw_lines(t_game *game, t_ray *ray, int draw_start, int draw_end);

/* drawing_utils.c */

void	swap_coordinates(t_point *p1, t_point *p2);
void	pixel_put(t_img *data, t_point p, int color);

/* minimap.c */

void	draw_map(t_game *game);

/* textures.c */

int		load_textures(t_game *game);
void	draw_textured_slice(t_game *game, t_ray *ray, t_texture	texture);

/* init.c */

int		init(t_mlx *mlx, t_game *game, t_map *map, char *map_path);

/* from ft_printf utils */

int		char_is_in_str(char c, char *str);

#endif
