/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:48 by stempels          #+#    #+#             */
/*   Updated: 2025/04/09 16:17:59 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_map(t_data *data, char *mapfile, int ***map);
static int	get_y(t_data *data, int fd, int ***map);
static int	check_arg(char **argv);
static int	check_str(char **array, int ***map, int width, int line_length);
static int	check_map(char *arg);
int	ft_isint(char *str);
int	in_base(char c, char *base);

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc != 2)
		return (-1);
	i = ft_strlen(argv[1]);
	if (i < 5 || ft_abs(ft_memcmp(&argv[1][i - 4], ".fdf", 4)))
		return (-1);
	data.x_max = INT_MAX;
	data.y_max = 0;
	data.z_min = INT_MAX;
	data.z_max = INT_MIN;
	parse_map(&data, argv[argc - 1], data.map);
	if (!data.map[0] || !data.map[1])
		return (-1);
	fdf(&data);
	return (0);
}
/*
	i = 0;
	while (i < data.y_max)
	{
		j = 0;
		while (j < data.x_max)
		{
			printf("%d ", map[0][i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
*/

static int	parse_map(t_data *data, char *mapfile, int ***map)
{
	int		fd;
	char	*line;

	fd = open(mapfile, 'r');
	if (read(fd, 0, 0) == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		data->y_max++;
	}
	close(fd);
	fd = open(mapfile, 'r');
	map[0] = (int **) malloc(sizeof(int *) * data->y_max);
	if (!map[0])
		return (0);
	map[1] = (int **) malloc(sizeof(int *) * data->y_max);
	if (!map[1])
		return (free(map[0]), 0);
	get_y(data, fd, map);
	return (1);
}

static int	get_y(t_data *data, int fd, int ***map)
{
	int		i;
	char	*line;
	char	**arg;

	i = 0;
	while (i < data->y_max)
	{
		line = get_next_line(fd);
		if (!line)
			return (close_all(data), 0);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = ' ';
		arg = ft_split(line, ' ');
		free(line);
		if (!arg || (data->x_max < INT_MAX
				&& ft_arrlen(arg) != (size_t)data->x_max))
			return (arr_free(arg), close_all(data), 0);
		data->x_max = ft_arrlen(arg);
		if (!check_arg(arg) || !check_str(arg, map, i, data->x_max))
			return (arr_free(arg), close_all(data), 0);
		i++;
		arr_free(arg);
	}
	close(fd);
	return (1);
}

static int	check_arg(char **argv)
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

static int	check_str(char **array, int ***map, int width, int length)
{
	int		i;
	char	**arg;

	map[0][width] = (int *) malloc(sizeof(int) * length);
	if (!map[0])
		return (0);
	map[1][width] = (int *) malloc(sizeof(int) * length);
	if (!map[1])
		return (free(map[0][width]), 0);
	i = 0;
	while (array[i])
	{
		arg = ft_split(array[i], ',');
		if (!arg[0])
			return (0);
		map[0][width][i] = check_map(arg[0]);
		if (map[0][width][i] == 0 && !arg)
			return (0);
		map[1][width][i] = check_map(arg[1]);
		if (map[1][width][i] == 0 && !arg)
			return (0);
		i++;
		arr_free(arg);
	}
	return (1);
}

static int	check_map(char *arg)
{
	int	content;

	if (arg)
	{
		if (arg[0] == '0' && arg[1] == 'x')
			content = ft_atoi_base(&arg[2], BA_X16);
		else
			content = ft_atoi_base(arg, BA_X16);
		if ((content == -1 && arg[0] != '-')
			|| (content == 0 && arg[0] != '0'))
			return (free(arg), 0);
	}
	else
		content = 0x00FFFFFF;
	return (content);
}

int	ft_isint(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 8;
	if (str[i] == '+' || str[i] == '-')
			i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			break;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	if (str[i++] == ',')
	{
		if (str[i] == '0' && str[i + 1] == 'x')
			i = i + 2;
		while (str[i] && j > 0)
		{
			str[i] = ft_toupper(str[i]);
			if (!in_base(str[i], BA_X16))
				break ;
			i++;
			j--;
		}
		if (str[i] == '\0' && j == 0)
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
