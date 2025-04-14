/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:13:57 by stempels          #+#    #+#             */
/*   Updated: 2025/04/14 10:05:57 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*init_point_struct(t_data *data, int x, int y, int ***map)
{
	float		projx;
	float		projy;
	float	angle;
	t_point	*ptx;

	angle = -M_PI / 6;
	ptx = (t_point *) malloc(sizeof(t_point) * 1);
	if (!ptx)
		return (NULL);
	projx = (x * (WIDHT / (data->x_max)));
	projy = (y * (HEIGHT / (data->y_max)));
//	ptx->x = (x * (WIDHT / (data->x_max)));
//	ptx->y = (y * (HEIGHT / (data->y_max)));
	ptx->x = (int)((projx + projy) * cos(angle));
	ptx->y = (int)((projx - projy) * sin(angle) - map[0][y][x]);
	ptx->color = map[1][y][x];
	ptx->x = (ptx->x + ft_abs(data->min_x)) * 0.66;
	ptx->y = (ptx->y + ft_abs(data->min_z)) * 0.66;
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
