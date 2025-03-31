/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:05:23 by stempels          #+#    #+#             */
/*   Updated: 2025/03/31 14:37:31 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_F
# define FDF_F
# include "libft.h"
# include "mlx.h"
/*---------------------------MACRO--------------------------------------------*/
# define EXT_FDF ".fdf"
# define WIDHT 1920
# define HEIGHT 1080 
# define RESOLUTION WIDHT HEIGHT
/**/
/*---------------------------STRUC--------------------------------------------*/
typedef struct	s_data
{
	void	*img;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
}		t_data;

typedef struct	s_point
{
	int			x;
	t_point		xp;
	t_point		xn;
	int			y;
	t_point		yp;
	t_point		yn;
	int			z;
	unsigned int	color;
}		t_point;
/**/
/*---------------------------FONCT--------------------------------------------*/
/**/
/*---------------------------UTILS--------------------------------------------*/
/**/

#endif
