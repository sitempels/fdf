/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:17:16 by stempels          #+#    #+#             */
/*   Updated: 2025/04/10 14:56:56 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
/*---------------------------MACRO--------------------------------------------*/
# define WIDHT 1920
# define HEIGHT 1080 
# define ESC_KEY 65307
/**/
/*---------------------------STRUC--------------------------------------------*/
typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		**map[2];
	int		x_max;
	int		y_max;
	int		z_min;
	int		z_max;
}		t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}		t_point;
/**/
/*---------------------------FONCT--------------------------------------------*/
void	fdf(t_data *img);
/**/
/*---------------------------UTILS--------------------------------------------*/
int		**free_on_close(int fd, char **arstr, int i, int **arint);
int		close_all(t_data *data, int fd);
void	my_mlx_pxput(t_data *data, int x, int y, unsigned int color);
t_point	*init_point_struct(t_data *data, int x, int y, int ***map);
/**/

#endif
