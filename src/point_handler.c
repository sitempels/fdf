/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:13:57 by stempels          #+#    #+#             */
/*   Updated: 2025/04/09 15:28:01 by stempels         ###   ########.fr       */
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
	projx = (x * (WIDHT / (data->x_max - 1)));
	projy = (y * (HEIGHT / (data->y_max - 1)));
	ptx->x = (int)((projx + projy) * cos(angle));
	ptx->y = (int)((projx - projy) * sin(angle) - map[0][x][y]);
	ptx->color = map[1][x][y];
	ptx->x = (ptx->x * 0.5) + 0.05 * WIDHT;
	ptx->y = (ptx->y * 0.5) + 0.5 * HEIGHT;
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
