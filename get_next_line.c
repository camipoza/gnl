/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:15:55 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/04 19:59:12 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static int i;
    char *buffer;
    char *str;
    int readbytes;
    int txt1;
    int txt2;
    size_t lenline;
    char *line;

    readbytes = read(fd, buffer, BUFFER_SIZE);
    if(readbytes == -1)
        perror("error al leer archivo");
	buffer[readbytes] = '\0';

	while(buffer[readbytes] != '\0')
	{
		str = ft_strchr(buffer, '\n');
		txt1 = ft_strlen(buffer);
    	txt2 = ft_strlen(str);
		lenline = txt1 - txt2;
    	line = ft_substr(buffer, i, lenline);
		return(line);
	}

    // ft_read
   // ft_extract_and_free_line
    return buffer;
}

int main(int argc, char **argv)
{
    int fd;
    char *readlines;

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
    readlines = get_next_line(fd);
    printf("%s", readlines);
    close (fd);
    return (0);
}