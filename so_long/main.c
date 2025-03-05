/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:34:58 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 13:25:42 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	game = NULL;
	map = NULL;
	arg_validation(argc, argv[1]);
	map_struct_init(&map);
	map_validation(argv[1], map);
	game_struct_init(&game, map);
	start_window(map, game);
	free_game_struct(game);
	free_map_struct(map);
	return (0);
}
