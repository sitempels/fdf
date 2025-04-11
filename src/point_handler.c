/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:13:57 by stempels          #+#    #+#             */
/*   Updated: 2025/04/11 16:16:31 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*init_point_struct(t_data *data, int x, int y, int ***map)
{
	int		projx;
	int		projy;
	float	angle;
	t_point	*ptx;

	angle = M_PI / 6;
	ptx = (t_point *) malloc(sizeof(t_point) * 1);
	if (!ptx)
		return (NULL);
	projx = (x * ((data->max_x - data->min_x) / (data->x_max)));
	projy = (y * ((data->max_z - data->min_z) / (data->y_max)));
	ptx->x = (int)((projx + projy) * cos(angle));
	ptx->y = (int)((projx - projy) * sin(angle) - map[0][x][y]);
	ptx->color = map[1][x][y];
	ptx->x = (ptx->x * 0.8 + ((WIDHT - data->max_x + data->min_x) / 2));
	ptx->y = (ptx->y * 0.8 + ((HEIGHT - data->max_z + data->min_z) / 2));
	return (ptx);
}

void	my_mlx_pxput(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x > WIDHT || y < 0 || y > HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
