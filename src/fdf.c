/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:55 by stempels          #+#    #+#             */
/*   Updated: 2025/04/04 16:18:44 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pxput(t_data *data, int x, int y, int color);
void	draw_line(t_data *data, t_point *pt1, t_point *pt2);
t_point *init_point_struct(t_data *img, int x, int y, int z);

void	fdf(t_data *img, int **map)
{
	int	i;
	int	j;
	void	*mlx_cnx;
	void	*mlx_win;
	t_point	*ptx1;
	t_point	*ptx2;
	
	mlx_cnx = mlx_init();
	mlx_win = mlx_new_window(mlx_cnx, WIDHT, HEIGHT, "title");
	img->img = mlx_new_image(mlx_cnx, WIDHT, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	i = 0;
	while (i < img->y_max)
	{
		j = 0;
		ptx1 = init_point_struct(img, j, i, map[i][j]);
		while (j < img->x_max)
		{
			ptx2 = init_point_struct(img, j, i, map[i][j]);
			draw_line(img, ptx1, ptx2);
		//	my_mlx_pxput(img, ptx2->x, ptx2->y, 0x0000FF00);
			ptx1 = ptx2;
			j++;
		}
		my_mlx_pxput(img, ptx2->x, ptx2->y, 0x0000FF00);
		i++;
	}
	j = 0;
	while (j < img->x_max)
	{
		i = 0;
		ptx1 = init_point_struct(img, j, i, map[i][j]);
		while (i < img->y_max)
		{
			ptx2 = init_point_struct(img, j, i, map[i][j]);
			draw_line(img, ptx1, ptx2);
			ptx1 = ptx2;
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx_cnx, mlx_win, img->img, 0, 0);
	mlx_loop(mlx_cnx);
	return ;
}

t_point *init_point_struct(t_data *img, int x, int y, int z)
{
	float	angle;
	t_point	*ptx;

	angle =  M_PI / 6;
	ptx = (t_point *) malloc(sizeof(t_point) * 1);
	if (!ptx)
		return (NULL);
	x = (x * (WIDHT * 0.50 / (img->x_max - 1))) + WIDHT * 0.1 + ((int)(WIDHT * 0.8) % (img->x_max - 1) / 2);
	y = (y * (HEIGHT * 0.50 / (img->y_max - 1))) + HEIGHT * 0.1 + ((int)(HEIGHT * 0.8) % (img->y_max - 1) / 2);
	ptx->x = (int)((x + y) * cos(angle));
	ptx->y = (int)((x - y) * sin(angle) - z);
	ptx->color = 0x00FFFFFF;
	return (ptx);
}

void	draw_line(t_data *data, t_point *pt1, t_point *pt2)
{
	int		i;
	int		len;
	float	dx;
	float	dy;
	float	steps[2];
	float	p[2];

	dx = pt2->x - pt1->x;
	dy = pt2->y - pt1->y;
	len = ft_abs(dy);
	if (ft_abs(dx) > ft_abs(dy))
		len = ft_abs(dx);
	steps[0] = dx / (float)len;
	steps[1] = dy / (float)len;
	p[0] = pt1->x;
	p[1] = pt1->y;
	i = 0;
	while (i <= len)
	{

		my_mlx_pxput(data, (int)p[0], (int)p[1], 0x00FFFFFF);
		p[0] += steps[0];
		p[1] += steps[1];
		i++;
	}
}

void	my_mlx_pxput(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIDHT || y < 0 || y > HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
