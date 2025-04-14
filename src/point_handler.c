/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:13:57 by stempels          #+#    #+#             */
/*   Updated: 2025/04/14 12:27:56 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	modif(int start, int end, float t);

t_point	*init_point_struct(t_data *data, int x, int y, int ***map)
{
	float	projx;
	float	projy;
	float	angle;
	t_point	*ptx;

	angle = -M_PI / 6;
	ptx = (t_point *) malloc(sizeof(t_point) * 1);
	if (!ptx)
		return (NULL);
	projx = (x * (WIDHT / (data->x_max)));
	projy = (y * (HEIGHT / (data->y_max)));
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

void	draw_line(t_data *data, t_point *pt1, t_point *pt2)
{
	int		i;
	int		len;
	float	dx;
	float	dy;
	float	pt[4];

	dx = pt2->x - pt1->x;
	dy = pt2->y - pt1->y;
	len = ft_abs(dy);
	if (ft_abs(dx) > ft_abs(dy))
		len = ft_abs(dx);
	pt[0] = dx / (float)len;
	pt[1] = dy / (float)len;
	pt[2] = pt1->x;
	pt[3] = pt1->y;
	i = 0;
	while (i <= len)
	{
		my_mlx_pxput(data, (int)pt[2], (int)pt[3],
			gc(pt1, pt2, i / (float)len));
		pt[2] += pt[0];
		pt[3] += pt[1];
		i++;
	}
}

int	gc(t_point *pt1, t_point *pt2, float t)
{
	int	red;
	int	green;
	int	blue;

	red = modif((pt1->color >> 16) & 0xFF, (pt2->color >> 16) & 0xFF, t);
	green = modif((pt1->color >> 8) & 0xFF, (pt2->color >> 8) & 0xFF, t);
	blue = modif(pt1->color & 0xFF, pt2->color & 0xFF, t);
	return (red << 16 | green << 8 | blue);
}

static int	modif(int start, int end, float t)
{
	return ((int)(start + (end - start) * t));
}
