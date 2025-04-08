/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:55 by stempels          #+#    #+#             */
/*   Updated: 2025/04/08 23:09:41 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_handler(int keycode, t_data *vars);
void	my_mlx_pxput(t_data *data, int x, int y, unsigned int color);
void	draw_line(t_data *data, t_point *pt1, t_point *pt2);
t_point *init_point_struct(t_data *img, int x, int y, int ***map);

void	fdf(t_data *data, int ***map)
{
	int	i;
	int	j;
	t_point	*ptx1;
	t_point	*ptx2;
	
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDHT, HEIGHT, "fdf");
	data->img = mlx_new_image(data->mlx, WIDHT, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
	mlx_hook(data->win, 2, 1L << 0, key_handler, data);
	mlx_hook(data->win, 17, 0, close_all, data);
	i = 0;
	while (i < data->y_max)
	{
		j = 0;
		ptx1 = init_point_struct(data, i, j, map);
		while (j < data->x_max)
		{
			ptx2 = init_point_struct(data, i, j, map);
			draw_line(data, ptx1, ptx2);
			free(ptx1);
			ptx1 = ptx2;
			j++;
		}
		my_mlx_pxput(data, ptx2->x, ptx2->y, map[1][i][j]);
		free(ptx2);
		i++;
	}
	j = 0;
	while (j < data->x_max)
	{
		i = 0;
		ptx1 = init_point_struct(data, i, j, map);
		while (i < data->y_max)
		{
			ptx2 = init_point_struct(data, i, j, map);
			draw_line(data, ptx1, ptx2);
			free(ptx1);
			ptx1 = ptx2;
			i++;
		}
		j++;
		free(ptx1);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
	return ;
}

static int	key_handler(int keycode, t_data *vars)
{
	if (keycode == ESC_KEY)
		close_all(vars);
	return (0);
}

int	close_all(t_data *data)
{
	if (!data)
		exit(0);
	if (data->map[0])
		arrint_free(data->map, data->y_max);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

t_point *init_point_struct(t_data *data, int x, int y, int ***map)
{
	int	projx;
	int	projy;
	float	angle;
	t_point	*ptx;

	angle =  M_PI / 6;
	ptx = (t_point *) malloc(sizeof(t_point) * 1);
	if (!ptx)
		return (NULL);
	projx = (x * (WIDHT / (data->x_max - 1)));
	projy = (y * (HEIGHT / (data->y_max - 1)));
	ptx->x = (int)((projx + projy) * cos(angle));
	ptx->y = (int)((projx - projy) * sin(angle) - map[0][x][y]) + (HEIGHT) * sin(angle);
	ptx->color = map[1][x][y];
	ptx->x = (ptx->x * 0.66) + 0.05 * WIDHT;
	ptx->y = (ptx->y * 0.66) + 0.3 * HEIGHT;
	return (ptx);
}

void	draw_line(t_data *data, t_point *pt1, t_point *pt2)
{
	int		i;
	int		len;
	float	dx;
	float	dy;
	float	dc;
	float	steps[3];
	float	p[3];

	dx = pt2->x - pt1->x;
	dy = pt2->y - pt1->y;
	dc = pt2->color - pt1->color;
	len = ft_abs(dy);
	if (ft_abs(dx) > ft_abs(dy))
		len = ft_abs(dx);
	steps[0] = dx / (float)len;
	steps[1] = dy / (float)len;
	steps[2] = dc / (float)len;
	p[0] = pt1->x;
	p[1] = pt1->y;
	p[2] = pt1->color;
	i = 0;
	while (i <= len)
	{

		my_mlx_pxput(data, (int)p[0], (int)p[1], (int)p[2]);
		p[0] += steps[0];
		p[1] += steps[1];
		p[2] += steps[2];
		i++;
	}
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
