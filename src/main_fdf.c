/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:48 by stempels          #+#    #+#             */
/*   Updated: 2025/04/07 15:30:33 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	***parse_map(t_data *data, char *mapfile);
static int	check_arg(char **argv);
static int	check_str(char **array, int ***map, int  width, int line_length);

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	int		***map;
	t_data	data;

	if (argc != 2)
		return (-1);
	j = ft_strlen(EXT_FDF);
	i = ft_strlen(argv[1]);
	if (i < j + 1)
		return (-1);
	i = i - j;
	while (--j >= 0)
		if (argv[1][i + j] != EXT_FDF[j])
			return (-1);
	data.x_max = INT_MAX;
	data.y_max = 0;
	map = parse_map(&data, argv[argc - 1]);
	if (!map)
		return (-1);
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
	fdf(&data, map);
	return (0);
}

static int	***parse_map(t_data *data, char *mapfile)
{
	int		i;
	int		fd;
	char	*line;
	char	**arg;
	int	***map;

	fd = open(mapfile, 'r');
	if (read(fd, 0, 0) == -1)
		return (NULL);
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
	map = (int ***) malloc(sizeof(int **) * 2);
	map[0] = (int **) malloc(sizeof(int *) * data->y_max);
	map[1] = (int **) malloc(sizeof(int *) * data->y_max);
	i = 0;
	while (i < data->y_max)
	{
		line = get_next_line(fd); 
		if (!line)
			return (NULL) ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = ' ';
		arg = ft_split(line, ' ');
		free(line);
		if (!arg)
			return (NULL);
		if (data->x_max < INT_MAX
			&& ft_arrlen(arg) != (size_t)data->x_max)
			return (NULL);
		data->x_max = ft_arrlen(arg);
		if (!check_arg(arg)
			|| !check_str(arg, map, i, data->x_max))
			return (NULL);
		i++;
		arr_free(arg);
	}
	return (map);
}

static int	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] == '-' || argv[i][j] == '+')
				&& (j < (int)ft_strlen(argv[i])
				&& !ft_isdigit(argv[i][j + 1])))
				return (0);
			if ((argv[i][j] == '-' || argv[i][j] == '+')
				&& (j > 0 && !ft_isspace(argv[i][j - 1])))
				return (0);
			if (!ft_isdigit(argv[i][j])
				&& !ft_isspace(argv[i][j])
				&& !(argv[i][j] == '-' || argv[i][j] == '+'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_str(char **array, int ***map, int width, int length)
{
	int	i;
	int	content;
	int	color;
	char	**arg;

	map[0][width] = (int *) malloc(sizeof(int) * length);
	if (!map[0])
		return (0);
	map[1][width] = (int *) malloc(sizeof(int) * length);
	if (!map[1])
		return (0);
	i = 0;
	while (array[i])
	{
		arg = ft_split(array[i], ',');
		if (!arg[0])
			return (0);
		content = ft_atoi(arg[0]);
		if ((content == -1 && arg[0][0] != '-')
			|| (content == 0 && arg[0][0] != '0'))
			return (0);
		if (arg[1])
		{
			color = ft_atoi(arg[1]);
			if ((color == -1 && arg[1][0] != '-')
				|| (color == 0 && arg[1][0] != '0'))
				return (0);
		}
		else
			color = 0x00FFFFFF;
		map[0][width][i] = content;
		map[1][width][i] = color;
		i++;
	}
	return (1);
}
