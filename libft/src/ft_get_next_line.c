/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:09:09 by stempels          #+#    #+#             */
/*   Updated: 2025/04/03 11:05:55 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gnl_read(int fd, char **inreading);
static char	*gnl_split(int fd, char **inreading, size_t n);
static char	*gnl_free(int fd, char **to_free);
static char	*gnl_join(int fd, char **s1, char *s2, size_t byte_read);

char	*get_next_line(int fd)
{
	size_t		i;
	static char	*inreading[FOPEN_MAX + 1];
	char		*new_line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (gnl_free(fd, inreading));
	i = -1;
	if (inreading[fd])
		while (inreading[fd][++i])
			if (inreading[fd][i] == '\n')
				return (gnl_split(fd, inreading, i + 1));
	new_line = gnl_read(fd, inreading);
	return (new_line);
}

static char	*gnl_read(int fd, char **inreading)
{
	char	buffer[BUFFER_SIZE];
	size_t	i;
	size_t	byte_read;

	byte_read = BUFFER_SIZE;
	while (byte_read == BUFFER_SIZE)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read <= 0 && !inreading[fd])
			return (gnl_free(fd, inreading));
		inreading[fd] = gnl_join(fd, inreading, buffer, byte_read);
		if (!inreading[fd])
			return (NULL);
		i = -1;
		while (inreading[fd][++i])
			if (inreading[fd][i] == '\n')
				return (gnl_split(fd, inreading, i + 1));
		if (inreading[fd] && byte_read < BUFFER_SIZE)
			return (gnl_split(fd, inreading, i));
	}
	return (NULL);
}

static char	*gnl_join(int fd, char **s1, char *s2, size_t byte_read)
{
	char	*s3;
	size_t	len;
	size_t	i;

	if (!s1[fd])
		len = 0;
	else
		len = ft_strlen(s1[fd]);
	if (!s2)
		byte_read = 0;
	s3 = (char *) malloc(sizeof(char) * (len + byte_read + 1));
	if (!s3)
		return (gnl_free(fd, s1));
	i = -1;
	while (++i < len)
		s3[i] = s1[fd][i];
	i = -1;
	while (++i < byte_read)
		s3[len + i] = s2[i];
	s3[len + byte_read] = '\0';
	free(s1[fd]);
	return (s3);
}

static char	*gnl_split(int fd, char **inreading, size_t n)
{
	size_t	i;
	size_t	len;
	char	*new_line;

	new_line = (char *) malloc(sizeof(char) * (n + 1));
	if (!new_line)
		return (gnl_free(fd, inreading));
	len = ft_strlen(inreading[fd]);
	i = -1;
	while (++i < n)
		new_line[i] = inreading[fd][i];
	new_line[n] = '\0';
	if (n < len)
	{
		i = -1;
		while (++i < len - n)
			inreading[fd][i] = inreading[fd][n + i];
		inreading[fd][i] = '\0';
	}
	else
		gnl_free(fd, inreading);
	return (new_line);
}

static char	*gnl_free(int fd, char **to_free)
{
	if (to_free[fd])
	{
		free(to_free[fd]);
		to_free[fd] = NULL;
	}
	return (NULL);
}
