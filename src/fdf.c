/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:55 by stempels          #+#    #+#             */
/*   Updated: 2025/04/14 12:25:33 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf1(t_data *data, int x_max, int y_max);
static void	fdf2(t_data *data, int x_max, int y_max);
static int	key_handler(int keycode, t_data *vars);

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
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_length, &data->endian);
	if (!data->addr)
		return (close_all(data, 0));
	mlx_hook(data->win, 2, 1L << 0, key_handler, data);
	mlx_hook(data->win, 17, 0, close_all, data);
	fdf1(data, data->x_max, data->y_max);
	fdf2(data, data->x_max, data->y_max);
	dx = WIDHT * 0.1;
	dy = HEIGHT * 0.1;
	mlx_put_image_to_window(data->mlx, data->win, data->img, dx, dy);
	mlx_loop(data->mlx);
	return (1);
}

static void	fdf1(t_data *data, int x_max, int y_max)
{
	int		i;
	int		j;
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

static void	fdf2(t_data *data, int x_max, int y_max)
{
	int		i;
	int		j;
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

static int	key_handler(int keycode, t_data *vars)
{
	if (keycode == ESC_KEY)
		close_all(vars, 0);
	return (0);
}
