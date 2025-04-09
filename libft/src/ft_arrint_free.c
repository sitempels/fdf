/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrint_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:08:01 by stempels          #+#    #+#             */
/*   Updated: 2025/04/09 10:08:32 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	arrint_free(int	***array, int i)
{
	int	m;
	int	n;

	n = 0;
	while (n < 2)
	{
		m = 0;
		while (m < i)
		{
			if (array[n][m])
				free(array[n][m]);
			m++;
		}
		if (array[n])
			free(array[n]);
		array[n] = NULL;
		n++;
	}
	array = NULL;
}
