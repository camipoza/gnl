/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paco07.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werodrig <werodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:31:41 by werodrig          #+#    #+#             */
/*   Updated: 2025/02/02 17:24:33 by werodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	test_gnl(int fd, const char *str)
{
	char	*res;

	res = get_next_line(fd);
	if (res == NULL && str == NULL)
		printf("✔\n");
	else if (res == NULL)
		printf("✘ gnl is null\n");
	else if  (str == NULL)
		printf("✘ exp is null\n");
	else
	{
		if (strcmp(res, str) == 0)
			printf("✔\n");
		else
			printf("✘ gnl: %s, exp: %s\n", res, str);
	}
	if (res)
		free(res);
}

int	main(void)
{
	int	fd;

	fd = open("07.txt", O_RDONLY);
	if (fd == -1)
		return (printf("✘ No file\n"));
	test_gnl(fd, "aaaaaaaaaa\n");
	test_gnl(fd, "bbbbbbbbbb\n");

	close(fd);
	test_gnl(fd, NULL);
	
	fd = open("07.txt", O_RDONLY);

	test_gnl(fd, "aaaaaaaaaa\n");
	test_gnl(fd, "bbbbbbbbbb\n");
	test_gnl(fd, "cccccccccc\n");
	test_gnl(fd, "dddddddddd\n");
	test_gnl(fd, NULL);
	close(fd);
}
