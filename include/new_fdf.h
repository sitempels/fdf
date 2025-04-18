/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fdf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:05:23 by stempels          #+#    #+#             */
/*   Updated: 2025/04/04 17:57:11 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_F
# define FDF_F
# include "libft.h"
# include "mlx.h"
# include <math.h>
/*---------------------------MACRO--------------------------------------------*/
# define EXT_FDF ".fdf"
# define WIDHT 1920
# define HEIGHT 1080 
# define RESOLUTION WIDHT HEIGHT
/**/
/*---------------------------STRUC--------------------------------------------*/
typedef struct	s_data
{
	int	x_max;
	int	y_max;
	void	*img;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
}		t_data;

typedef struct	s_line
{
	t_point	*line;
	t_line	*next;
}		t_line;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	unsigned int	color;
	t_point		*next;
}		t_point;
/**/
/*---------------------------FONCT--------------------------------------------*/
void	fdf(t_data *img, int **map);
/**/
/*---------------------------UTILS--------------------------------------------*/
int	**free_on_close(int fd, char **arstr, int i, int **arint);
void	arr_free(char **array);
void	arrint_free(int **array, int i);
/**/

#endif
