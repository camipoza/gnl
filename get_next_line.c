/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:15:55 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/05 19:03:54 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *extract_line(char* buffer)
{
	char *inbuffer;
	int txt1;
	int txt2;
	size_t lenline;
	char *line;

	inbuffer = ft_strchr(buffer, '\n');
	txt1 = strlen(buffer);
	txt2 = strlen(inbuffer);
	lenline = txt1 - txt2;
	line = ft_substr(buffer, 0, lenline);
	return(line);
}

char *get_next_line(int fd)
{
	char *buffer;
	int readbytes;
	char *extracted;
	static char *rest;
	
	while(!ft_strchr(buffer, '/n'))
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if(readbytes == -1)
			perror("error al leer archivo");
		buffer[readbytes] = '\0';
		while(buffer[readbytes] != '\0')
		{
			extracted = extract_line;
			rest =
		}
	}
	
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