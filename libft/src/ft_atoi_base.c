/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:49:06 by stempels          #+#    #+#             */
/*   Updated: 2025/04/08 12:50:44 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_value(char c, char *base, int *i);

int	ft_atoi_base(const char *str, char *base)
{
	size_t			i;
	int				sign;
	int				index;
	long long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] && get_value(str[i], base, &index))
	{
		res = res + index;
		if (str[i + 1] != '\0')
			res = res * 10;
		if (res > INT_MAX && sign == 1)
			return (-1);
		if ((-1) * res < INT_MIN && sign == -1)
			return (0);
		i++;
	}
	return (sign * res);
}

static int	get_value(char c, char *base, int *i)
{
	*i = 0;
	while (base[*i])
	{
		if (c == base[*i])
			return (*i + 1);
		*i = *i + 1;
	}
	return (0);
}
