/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:48 by stempels          #+#    #+#             */
/*   Updated: 2025/03/31 15:27:10 by stempels         ###   ########.fr       */
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
	t_point	*map;

	i = ft_strlen(argv[argc - 1]);
	j = 4;
	while (--j <= 0)
		if (argv[argc - 1][i + j] != EXT_FDF[j])
			return (-1);
	map = parse_map(argv[argc - 1]);
	if (!map)
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

	mlx_put_image_to_window(mlx_cnx, mlx_win, img.img, 0, 0);
	return ;
}

t_point	*parse_map(char *mapfile)
{
	int	x;
	int	fd;
	char	*line;
	t_point	*map;

	fd = open(mapfile, 'r');
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	map = init_struct(line, 0);
	x = 1;
	while (!line)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		map = init_struct(line, x);
		if (!map)
			return (NULL);
		x++;
	}
	map = link_struct(map);
	if (!map)
		return (NULL);
	close (fd);
	return (map);
}

t_point	*init_struct(char *line, int x)
{
	int	i;
	t_point	pt;

	i = 0;
	while (line[i])
	{
		pt = (t_point) malloc(sizeof(t_point) * 1);	
	}
}

void	draw_line(t_data *data, t_point *pt1, t_point *pt2)
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
}

void	my_mlx_pxput(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
