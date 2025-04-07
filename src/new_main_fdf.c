/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main_fdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:51:48 by stempels          #+#    #+#             */
/*   Updated: 2025/04/07 14:54:54 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_input(int argc, char **argv);
static int	***parse_map(t_data *data, char *mapfile);
static int	check_arg(char **argv);
static int	check_str(char **array, int **map, int  width, int line_length);

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	int		**map[2];
	t_data	data;

	if (!check_input(argc, argv))
		return (0);
	data.x_max = INT_MAX;
	data.y_max = 0;
	map = parse_map(&data, argv[argc - 1]);
	if (!map[0] || ! map[1])
		return (-1);
	i = 0;
	while (i < data.y_max)
	{
		j = 0;
		while (j < data.x_max)
		{
			printf("%d ", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	fdf(&data, map);
	return (0);
}

static int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 2)
		return (0);
	j = ft_strlen(EXT_FDF);
	i = ft_strlen(argv[1]);
	if (i < j + 1)
		return (0);
	i = i - j;
	while (--j >= 0)
		if (argv[1][i + j] != EXT_FDF[j])
			return (0);
	return (1);

}

static int	***parse_map(t_data *data, char *mapfile)
{
	int		i;
	int		fd;
	char	*line;
	char	**arg;
	t_line	*map;

	fd = open(mapfile, 'r');
	if (read(fd, 0, 0) == -1)
		return (NULL);
	fd = open(mapfile, 'r');
	i = 0;
	while (1)
	{
		line = get_next_line(fd); 
		if (!line)
			return (NULL);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = ' ';
		map = (t_line *) malloc(sizeof(t_line) * 1);
		arg = ft_split(line, ' ');
		free(line);
		if (!arg)
			return (NULL);
		if (data->x_max < INT_MAX
			&& ft_arrlen(arg) != (size_t)data->x_max)
			return (free_on_close(-fd, arg, i, map));
		data->x_max = ft_arrlen(arg);
		if (!check_arg(arg)
			|| !check_str(arg, map, i, data->x_max))
			return (free_on_close(-fd, arg, i, map));
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

static int	check_str(char **array, int **map, int width, int length)
{
	int	i;
	int	content;

	map[width] = (int *) malloc(sizeof(int) * length);
	if (!map)
		return (0);
	i = 0;
	while (array[i])
	{
		content = ft_atoi(array[i]);
		if ((content == -1 && array[i][0] != '-')
			|| (content == 0 && array[i][0] != '0'))
			return (0);
		map[width][i] = content;
		i++;
	}
	return (1);
}
