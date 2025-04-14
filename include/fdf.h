/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:17:16 by stempels          #+#    #+#             */
/*   Updated: 2025/04/14 13:51:24 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
/*---------------------------MACRO--------------------------------------------*/
# ifndef WIDHT 
#  define WIDHT 1920
# endif
# ifndef HEIGHT 
#  define HEIGHT 1080
# endif
# ifndef ANGLE
#  define ANGLE -0.52 
# endif
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
	int		min_x;
	int		max_x;
	int		min_z;
	int		max_z;
}		t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}		t_point;
/**/
/*---------------------------FONCT--------------------------------------------*/
int		fdf(t_data *img);
/**/
/*---------------------------UTILS--------------------------------------------*/
int		**free_on_close(int fd, char **arstr, int i, int **arint);
int		close_all(t_data *data, int fd);
int		gc(t_point *pt1, t_point *pt2, float t);
int		in_base(char c, char *base);
int		check_arg(char **argv);
void	get_max(t_data *data);
void	my_mlx_pxput(t_data *data, int x, int y, unsigned int color);
void	draw_line(t_data *data, t_point *pt1, t_point *pt2);
t_point	*init_point_struct(t_data *data, int x, int y, int ***map);
/**/

#endif
