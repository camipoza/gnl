/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:15:55 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/27 17:33:05 by cpoza-ra         ###   ########.fr       */
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

int ft_untiln(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (-1);
	while(s[i] != '\n' && s[i] != '\0')
		i++;
	return(i);
}

char *ft_readbuffer(int fd, char *rest)
{
	char *buffer;
	int readbytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (!gnl_ft_strchr(rest, '\n'))
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free (buffer);
			return (NULL);
		}
		if (readbytes == 0)
			break;
		buffer[readbytes] = '\0';
		rest = gnl_ft_strjoin(rest, buffer);
	}
	free (buffer);
	return (rest);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *rest = NULL;
	int	linelen;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_readbuffer(fd, rest);
	linelen = ft_untiln(buffer);
	line = gnl_ft_substr(buffer, 0, linelen + 1);
	if (gnl_ft_strchr(buffer, '\n'))
		rest = gnl_ft_substr(buffer, linelen + 1, BUFFER_SIZE);
	else
		rest = NULL;
	free (buffer);
	return (line);
}

// int main(int argc, char **argv)
// {
// 	int fd;
// 	char *result;

// 	if (argc != 2)
// 	{
// 		printf("argumentos insuficientes");
// 		return (1);
// 	}

// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("error al abrir archivo");
// 		return (1);
// 	}
// 	result = get_next_line(fd);

// 	while (result)
// 	{
// 		printf("%s", result);
// 		free(result);
// 		result = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// } 