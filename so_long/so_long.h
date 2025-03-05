/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:45:13 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 15:44:41 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include "MLX42/include/MLX42/MLX42.h"

# define PIXEL 48

typedef struct s_map
{
	int		p_start_x;
	int		p_start_y;
	int		e_exit_x;
	int		e_exit_y;
	int		col_size;
	int		row_size;
	int		collectible_count;
	int		start_count;
	int		exit_count;
	int		collected;
	int		p_direction_flag;
	int		**visited;
	char	*map_name;
	char	**map_array;
}	t_map;

typedef struct s_game
{
	int				prev_x;
	int				prev_y;
	int				width;
	int				height;
	int				move_count;
	char			*name;
	mlx_texture_t	*collectible;
	mlx_texture_t	*exit_tile;
	mlx_texture_t	*wall;
	mlx_texture_t	*grass;
	mlx_texture_t	*prev;
	mlx_texture_t	*prev_v;
	mlx_texture_t	*player_down;
	mlx_texture_t	*player_right;
	mlx_texture_t	*player_left;
	mlx_texture_t	*player_up;
	mlx_texture_t	*up_left;
	mlx_texture_t	*up_right;
	mlx_texture_t	*down_right;
	mlx_texture_t	*down_left;
	mlx_image_t		*down_left_p;
	mlx_image_t		*down_right_p;
	mlx_image_t		*up_right_p;
	mlx_image_t		*up_left_p;
	mlx_image_t		*player_up_p;
	mlx_image_t		*player_left_p;
	mlx_image_t		*player_right_p;
	mlx_image_t		*prev_v_p;
	mlx_image_t		*player_down_p;
	mlx_image_t		*collectible_p;
	mlx_image_t		*exit_tile_p;
	mlx_image_t		*wall_p;
	mlx_image_t		*grass_p;
	mlx_image_t		*prev_p;
	mlx_t			*mlx;
	t_map			*map;
}	t_game;
// Argument validation
void	arg_validation(int argc, char *argv);
int		main(int argc, char **argv);
// Flood fill functions
void	count_collectibles(t_map *map_point);
void	find_start_point(t_map *map_point);
void	find_exit_point(t_map *map_point);
void	visited_array_alloc(t_map *map_point);
// Map validation
int		get_fd(char *file_name);
void	map_validation(char *map, t_map *map_point);
int		row_size(char **line);
int		col_size(char *map);
void	rectangular_check(int fd, t_map *map_point);
void	wall_check(t_map *map_point);
void	flood_fill_check(t_map *map_point);
// Error Handeling
void	print_error(char *msg);
// Free operations.
void	free_buffer_close(char *line, int fd);
void	free_matrix(char **matrix);
void	free_int_matrix(int **matrix, int rows);
void	free_map_struct(t_map *map_point);
void	free_game_struct(t_game *game);
void	free_rectangular_fail(t_map *map_point, char *line, int fd);
// Struct handeling
void	map_struct_init(t_map **map);
void	game_struct_init(t_game **game, t_map *map);
// Window managment
void	start_window(t_map *map, t_game *game);
void	texture_to_image(mlx_t *mlx, t_game *game, t_map *map);
// Handle key press
void	handle_keypress(mlx_key_data_t keydata, void *param);
void	move_p_down(t_game *game, int new_x, int new_y, int prev_dir);
void	move_p_up(t_game *game, int x_pixel, int y_pixel, int prev_dir);
void	move_p_left(t_game *game, int x_pixel, int y_pixel, int prev_dir);
void	move_p_right(t_game *game, int x_pixel, int y_pixel, int prev_dir);
#endif
