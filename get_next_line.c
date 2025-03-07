/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:15:55 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/07 17:37:38 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_readbuffer(int fd, char *r)
{
	char buffer[BUFFER_SIZE + 1];
	int readbytes;
	
	while(!gnl_ft_strchr(r, '\n'))
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if(readbytes <= 0)
			return (NULL);
		buffer[readbytes] = '\0';
		r = gnl_ft_strjoin(r, buffer);
	}
	return(r);
}

char *ft_extract_line(char *buffer)
{
	int txt1;
	int txt2;
	size_t lenline;
	char *line;

	txt1 = gnl_ft_strlen(buffer);
	txt2 = gnl_ft_strlen(gnl_ft_strchr(buffer, '\n'));
	lenline = txt1 - txt2;
	line = gnl_ft_substr(buffer, 0, lenline +1);
	return(line);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *rest;

	buffer = ft_readbuffer(fd, rest);
	line = ft_extract_line(buffer);
	// printf("Line %s\n", line);
	rest = gnl_ft_strchr(buffer, '\n') + 1;
	// free(buffer);
	// buffer = rest;
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
    if(fd == -1)
    {
        perror("error al abrir archivo");
        return (1);
    }
    result = get_next_line(fd);
	printf("%s", result);
	    result = get_next_line(fd);
	printf("%s", result);

	// while(result)
	// {
	// 	printf("%s", result);
	// 	free (result);
	// 	result = get_next_line(fd);
	// }
    close (fd);
    return (0);
}