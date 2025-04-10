/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:03:21 by stempels          #+#    #+#             */
/*   Updated: 2025/04/10 13:29:03 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n, int param)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *) s;
	if (n == 0)
		return ;
	else
	{
		while (i < n)
			ptr[i++] = param;
	}
}
