/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:16:08 by stempels          #+#    #+#             */
/*   Updated: 2025/04/14 13:48:34 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_isint(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[i++] == ',')
	{
		if (str[i] == '0' && str[i + 1] == 'x')
			i = i + 2;
		j = -1;
		while (str[i + ++j] && j < 9)
		{
			str[i + j] = ft_toupper(str[i + j]);
			if (!in_base(str[i + j], BA_X16))
				break ;
		}
		if (str[i + j] == '\0' && (j == 6 || j == 8))
			return (1);
	}
	return (0);
}

int	in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (1);
		i++;
	}
	return (0);
}

void	get_max(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;

	j = 0;
	while (j < data->y_max)
	{
		i = 0;
		while (i < data->x_max)
		{
			x = (i * (WIDHT / data->x_max));
			y = (j * (HEIGHT / data->y_max));
			if ((x + y) * cos(ANGLE) > data->max_x)
				data->max_x = (x + y) * cos(ANGLE);
			if (((x - y) * sin(ANGLE) - data->map[0][j][i]) > data->max_z)
				data->max_z = (x - y) * sin(ANGLE) - data->map[0][j][i];
			if (((x - y) * sin(ANGLE) - data->map[0][j][i]) < data->min_z)
				data->min_z = (x - y) * sin(ANGLE) - data->map[0][j][i];
			i++;
		}
		j++;
	}
}

int	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (!ft_isint(argv[i]))
			return (0);
		while (argv[i][j])
		{
			if ((argv[i][j] == '-' || argv[i][j] == '+') && (j > 0
				&& !ft_isspace(argv[i][j - 1]))
				&& !ft_isspace(argv[i][j])
				&& (j < (int)ft_strlen(argv[i])
				&& !ft_isdigit(argv[i][j + 1]))
				&& !(argv[i][j] == '-' || argv[i][j] == '+'
				|| argv[i][j] == 'x' || argv[i][j] == ','))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
