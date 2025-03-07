/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:15:55 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/07 15:09:14 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_readbuffer(int fd, char *r)
{
	char buffer[BUFFER_SIZE];
	int readbytes;
	
	while(!gnl_ft_strchr(buffer, '/n'))
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if(readbytes == -1)
			perror("error al leer archivo");
		buffer[readbytes] = '\0';
		r = gnl_ft_strjoin(r, buffer);
	}
	return(r);
}

char *extract_line(char *buffer)
{
	int txt1;
	int txt2;
	size_t lenline;
	char *line;

	txt1 = gnl_ft_strlen(buffer);
	txt2 = gnl_ft_strlen(ft_strchr(buffer, '\n'));
	lenline = txt1 - txt2;
	line = gnl_ft_substr(buffer, 0, lenline);
	return(line);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *rest;

	buffer = ft_readbuffer(fd, rest);
	while(!buffer)
	{
		line = extract_line(buffer);
		rest = gnl_ft_strchr(line, '\n') + 1;
		free(buffer);
		buffer = rest;
	}
	return (buffer);
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
    if(fd == -1)
    {
        perror("error al abrir archivo");
        return (1);
    }
    result = get_next_line(fd);
    printf("%s", result);
    close (fd);
    return (0);
}