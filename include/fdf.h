/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:05:23 by stempels          #+#    #+#             */
/*   Updated: 2025/04/08 22:50:19 by stempels         ###   ########.fr       */
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
# define ESC_KEY 65307
/**/
/*---------------------------STRUC--------------------------------------------*/
typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
	int	**map[2];
	int	x_max;
	int	y_max;
	int	z_min;
	int	z_max;
}		t_data;

typedef struct	s_point
{
	int	x;
	int	y;
	int	color;
}		t_point;
/**/
/*---------------------------FONCT--------------------------------------------*/
void	fdf(t_data *img, int ***map);
/**/
/*---------------------------UTILS--------------------------------------------*/
int	**free_on_close(int fd, char **arstr, int i, int **arint);
int	close_all(t_data *data);
void	arr_free(char **array);
void	arrint_free(int ***array, int i);
void	ft_lstdelone(t_point *lst, void (*del)(int));
void	ft_lstclear(t_point **lst, void (*del)(int));
/**/

#endif
