/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:55 by stempels          #+#    #+#             */
/*   Updated: 2025/04/03 17:23:13 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pxput(t_data *data, int x, int y, int color);

void	fdf(t_data *img, int **map)
{
	int	i;
	int	j;
	int	m;
	int	n;
	void	*mlx_cnx;
	void	*mlx_win;
	
	mlx_cnx = mlx_init();
	mlx_win = mlx_new_window(mlx_cnx, WIDHT, HEIGHT, "title");
	img->img = mlx_new_image(mlx_cnx, WIDHT, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	i = 0;
	if (map)
	{
		i = 1;
		i--;
	}
	while (i < img->y_max)
	{
		j = 0;
		while (j < img->x_max)
		{
			m = (j * (WIDHT / (img->x_max - 1))) + (WIDHT % (img->x_max - 1) / 2);
			n = (i * (HEIGHT / (img->y_max - 1))) + (HEIGHT % (img->y_max - 1) / 2);
			my_mlx_pxput(img, m, n, 0x00FF0000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx_cnx, mlx_win, img->img, 0, 0);
	mlx_loop(mlx_cnx);
	return ;
}

/*void	draw_line(t_data *data, t_point *pt1, t_point *pt2)
{
	int	i;
	int	j;
	int	ptx;
	int	pty;

	i = 1;
	j = 1;
	ptx = pt1->x;
	pty = pt1->y;
	while (ptx < pt2->x || pty < pt2->y)
	{

		my_mlx_pxput(data, ptx, pty, ptcolor);
		ptx = ptx + (i++ / (pt2->x - pt1->x));
		pty = pty + (j++ / (pt2->x - pt1->x));
	}
}*/

void	my_mlx_pxput(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIDHT || y < 0 || y > HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
