/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:15:55 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/18 17:31:19 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *gnl_ft_strchr(char *s, char c)
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

size_t gnl_ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
		i++;
	return (i);
}

char *ft_readbuffer(int fd, char *rest)
{
	char buffer[BUFFER_SIZE + 1];
	int readbytes;

	while (!gnl_ft_strchr(rest, '\n'))
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == 0)
		{
			// free(rest);
			break;
		}
		if (readbytes == -1)
			return (NULL);
		buffer[readbytes] = '\0';
		rest = gnl_ft_strjoin(rest, buffer);
	}
	return (rest);
}

char *ft_extract_line(char *buffer)
{
	int linelen;
	char *line;

	if (!buffer)
		return (NULL);
	linelen = 0;
	while (buffer[linelen] != '\n' && buffer[linelen] != '\0')
		linelen++;
	if (buffer[linelen] == '\n')
		linelen++;
	line = gnl_ft_substr(buffer, 0, linelen);
	if (!line)
	{
		// free(line);
		return (NULL);
	}
	return (line);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *rest = NULL;
	size_t restlen;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rest)
	{
		buffer = rest;
		rest = NULL;
	}
	else
		buffer = ft_readbuffer(fd, rest);
	line = ft_extract_line(buffer);
	if (gnl_ft_strchr(buffer, '\n'))
	{
		restlen = gnl_ft_strlen(buffer) - gnl_ft_strlen(line);
		rest = gnl_ft_substr((gnl_ft_strchr(buffer, '\n') + 1), 0, restlen);
	}
	free(buffer);
	return (line);
}

int main(int argc, char **argv)
{
	int fd;
	char *result;

	if (argc != 2)
	{
		printf("argumentos insuficientes");
		return (1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("error al abrir archivo");
		return (1);
	}
	result = get_next_line(0);

	while (result)
	{
		printf("%s", result);
		free(result);
		result = get_next_line(0);
	}
	close(fd);
	return (0);
}