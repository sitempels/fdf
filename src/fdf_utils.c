/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:35:45 by stempels          #+#    #+#             */
/*   Updated: 2025/04/04 17:01:20 by stempels         ###   ########.fr       */
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
		arrint_free(arint, i);
	return (NULL);
}

void	arr_free(char **array)
{
	int	j;

	j = 0;
	while (array[j])
	{
		free(array[j]);
		j++;
	}
	free(array);
	array = NULL;
	return ;
}

void	arrint_free(int	**array, int i)
{
	int	m;

	m = 0;
	while (m < i)
	{
		if (array[m])
			free(array[m]);
		m++;
	}
	free(array);
	array = NULL;
}
