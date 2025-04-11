/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:35:45 by stempels          #+#    #+#             */
/*   Updated: 2025/04/11 14:54:41 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**free_on_close(int fd, char **arstr, int i, int **arint)
{
	if (fd < 0)
		get_next_line(fd);
	if (arstr)
		arr_free(arstr);
	if (arint && i > -1)
		arrint_free(&arint, i);
	return (NULL);
}

int	close_all(t_data *data, int fd)
{
	if (fd < 0)
		get_next_line(fd);
	if (!data)
		exit(0);
	if (data->map[0])
		arrint_free(data->map, data->y_max);
	if (data)
	{
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
			mlx_destroy_display(data->mlx);
		if (data->mlx)
			free(data->mlx);
	}
	exit(0);
}
