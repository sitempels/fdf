/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:55 by stempels          #+#    #+#             */
/*   Updated: 2025/04/14 10:08:13 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_handler(int keycode, t_data *vars);
static void	draw_line(t_data *data, t_point *pt1, t_point *pt2);
//static void	fdf2(t_data *data, int max_1, int max_2, int n);
static void	fdf3(t_data *data, int x_max, int y_max);
static void	fdf4(t_data *data, int x_max, int y_max);
int	modif(int start, int end, float t);
int	gc(t_point *pt1, t_point *pt2, float t);

int	fdf(t_data *data)
{
	int	dx;
	int	dy;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (close_all(data, 0));
	data->win = mlx_new_window(data->mlx, WIDHT, HEIGHT, "fdf");
	if (!data->win)
		return (close_all(data, 0));
	data->img = mlx_new_image(data->mlx, WIDHT, HEIGHT);
	if (!data->img)
		return (close_all(data, 0));
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
	if (!data->addr)
		return (close_all(data, 0));
	mlx_hook(data->win, 2, 1L << 0, key_handler, data);
	mlx_hook(data->win, 17, 0, close_all, data);
	fdf3(data, data->x_max, data->y_max);
	fdf4(data, data->x_max, data->y_max);
	dx = WIDHT * 0.1;
	dy = HEIGHT * 0.1;
	mlx_put_image_to_window(data->mlx, data->win, data->img, dx, dy);
	mlx_loop(data->mlx);
	return (1);
}
/*
static void	fdf2(t_data *data, int x_max, int y_max, int n)
{
	int	i;
	int	j;
	t_point	*ptx1;
	t_point	*ptx2;

	i = n;	
	while (i < y_max)
	{
		j = 0;
		ptx1 = init_point_struct(data, i - n, j, data->map);
		while (j < x_max)
		{
			ptx2 = init_point_struct(data, i, j, data->map);
			draw_line(data, ptx2, ptx1);
			free(ptx1);
			ptx1 = ptx2;
			j++;
		}
		my_mlx_pxput(data, ptx1->x, ptx1->y, ptx1->color);
		free(ptx1);
		i++;
	}
	return ;
}
*/
static void	fdf4(t_data *data, int x_max, int y_max)
{
	int	i;
	int	j;
	t_point	*ptx1;
	t_point	*ptx2;

	i = 0;	
	while (i < y_max)
	{
		j = 0;
		ptx1 = init_point_struct(data, j, i, data->map);
		while (j < x_max)
		{
			ptx2 = init_point_struct(data, j, i, data->map);
			draw_line(data, ptx2, ptx1);
			free(ptx1);
			ptx1 = ptx2;
			j++;
		}
		my_mlx_pxput(data, ptx1->x, ptx1->y, ptx1->color);
		free(ptx1);
		i++;
	}
	return ;
}


static void	fdf3(t_data *data, int x_max, int y_max)
{
	int	i;
	int	j;
	t_point	*ptx1;
	t_point	*ptx2;

	j = 0;	
	while (j < x_max)
	{
		i = 0;
		ptx1 = init_point_struct(data, j, i, data->map);
		while (i < y_max)
		{
			ptx2 = init_point_struct(data, j, i, data->map);
			draw_line(data, ptx2, ptx1);
			free(ptx1);
			ptx1 = ptx2;
			i++;
		}
		my_mlx_pxput(data, ptx1->x, ptx1->y, ptx1->color);
		free(ptx1);
		j++;
	}
	return ;
}

static int	key_handler(int keycode, t_data *vars)
{
	if (keycode == ESC_KEY)
		close_all(vars, 0);
	return (0);
}

static void	draw_line(t_data *data, t_point *pt1, t_point *pt2)
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
		my_mlx_pxput(data, (int)pt[2], (int)pt[3], gc(pt1, pt2, i / (float)len));
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

int	modif(int start, int end, float t)
{
	return ((int)(start + (end - start) * t));
}
