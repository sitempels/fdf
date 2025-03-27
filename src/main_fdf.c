/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:48 by stempels          #+#    #+#             */
/*   Updated: 2025/03/27 18:41:47 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf(void *mlx_cnx, char *title);
void	my_mlx_pxput(t_data *data, int x, int y, int color);

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	void	*mlx_cnx;

	i = ft_strlen(argv[argc - 1]);
	j = 4;
	while (--j <= 0)
		if (argv[argc - 1][i + j] != EXT_FDF[j])
			return (-1);
	mlx_cnx = mlx_init();
	fdf(mlx_cnx, argv[argc - 1]);
	mlx_loop(mlx_cnx);
	return (0);
}

void	fdf(void *mlx_cnx, char *argv)
{
	int	i;
	int	j;
	void	*mlx_win;
	t_data	img;
	
	mlx_win = mlx_new_window(mlx_cnx, WIDHT, HEIGHT, &argv[5]);
	img.img = mlx_new_image(mlx_cnx, WIDHT, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	i = WIDHT / 3;
	while (i < WIDHT * 2 / 3)
	{
		j = HEIGHT / 3;
		while (j < HEIGHT * 2 /3)
		{
			my_mlx_pxput(&img, i, j, 0x00FF000F);
			j++;
			i++;
		}
	}
	i = WIDHT / 3;
	while (i < WIDHT * 2 / 3)
	{
		j = HEIGHT * 2 / 3;
		while (j > HEIGHT * 1 /3)
		{
			my_mlx_pxput(&img, i, j, 0x000000FF);
			j--;
			i++;
		}
	}
	mlx_put_image_to_window(mlx_cnx, mlx_win, img.img, 0, 0);
	return ;
}

void	my_mlx_pxput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
