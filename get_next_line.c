/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:15:55 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/09 19:42:07 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


/* char *test(char *str)
{
	int	l1;
	int	l2;
	char *a;

	
	if (!str)
		return (NULL);
	l1 = gnl_ft_strlen(str);
	l2 = gnl_ft_strlen(gnl_ft_strchr(str, '\n'));
	a = gnl_ft_substr(str, (l1 - l2) + 1, l2 +  1);
	if(!a)
		return (NULL);
	return (a);
	
} */
char *ft_readbuffer(int fd, char *r)
{
	char buffer[BUFFER_SIZE + 1];
	int readbytes;
	
	while(!gnl_ft_strchr(r, '\n'))
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if(readbytes == 0)
			break;
		if(readbytes == -1)
			return (NULL);
		buffer[readbytes] = '\0';
		r = gnl_ft_strjoin(r, buffer);
	}
	return(r);
}

char *ft_extract_line(char *buffer)
{
	int linelen;
	char *line;

	linelen = 0;
	while (buffer[linelen] != '\n' && buffer[linelen] != '\0')
		linelen++;
	if (buffer[linelen] == '\n')
		linelen++;
	line = gnl_ft_substr(buffer, 0, linelen);
	return(line);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line;
	static char *rest;
	char *temp;

	if (rest && *rest)
	{
        buffer = rest;
        rest = NULL;
	} 
	else
		buffer = ft_readbuffer(fd, rest);

	line = ft_extract_line(buffer);

	temp = gnl_ft_strchr(buffer, '\n');
    if (temp)
        rest = gnl_ft_substr(temp + 1, 0, gnl_ft_strlen(buffer) - gnl_ft_strlen(line));
    else
        rest = NULL;
	
	if (!buffer || (rest == NULL && *buffer == '\0')) 
        return (line);
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
	while(result)
	{
		printf("%s", result);
		free (result);
		result = get_next_line(fd);
	}
    close (fd);
    return (0);
}