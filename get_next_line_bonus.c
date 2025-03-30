/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:49:16 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/30 18:40:51 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

char	*gnl_ft_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

int	ft_untiln(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_readbuffer(int fd, char *rest)
{
	char	*buffer;
	int		readbytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (!gnl_ft_strchr(rest, '\n'))
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free (buffer);
			// rest = NULL;
			return (NULL);
		}
		if (readbytes == 0)
			break ;
		buffer[readbytes] = '\0';
		rest = gnl_ft_strjoin(rest, buffer);
	}
	free (buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*rest[FOPEN_MAX];
	int			linelen;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	buffer = ft_readbuffer(fd, rest[fd]);
	if (!buffer)
		return (NULL);
	linelen = ft_untiln(buffer);
	line = gnl_ft_substr(buffer, 0, linelen + 1);
	if (gnl_ft_strchr(buffer, '\n'))
		rest[fd] = gnl_ft_substr(buffer, linelen + 1, BUFFER_SIZE);
	else
		rest[fd] = NULL;
	free (buffer);
	return (line);
}

/* int	main(int argc, char **argv)
{
	int fd;
    int fd2;
	char *result;
	char *result2;

 
	if (argc < 2)
	{
		printf("argumentos insuficientes");
		return (1);
	}

	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
    
	if (fd == -1)
	{
		perror("error al abrir archivo");
		return (1);
	}
    if (fd2 == -1)
	{
		perror("error al abrir archivo");
		return (1);
	}

	while (result || result2)
	{
        result = get_next_line(fd);
        result2 = get_next_line(fd2);
		printf("%s", result);
		free(result);
		printf("%s", result2);
		free(result2);
	}
	close(fd);
	close(fd2);
	return (0);
}  */