#include <unistd.h>
#include "libft.h"

int	ft_isint(char *str);
int	in_base(char c, char *base);

int	main(int argc, char **argv)
{
	int	test;
	char	res;

	test = ft_isint(argv[argc - 1]);
	res = test + 48;
	write(1, &res, 1);
	write(1, "\n", 1);
	return (0);
}

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
		if (str[i + j] == '\0' && j == 8)
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
