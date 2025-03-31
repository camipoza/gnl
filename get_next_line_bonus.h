/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:50:00 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/31 16:03:02 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_readbuffer(int fd, char *rest);
int		ft_untiln(const char *s);
char	*gnl_ft_strchr(char *s, char c);
size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_strncpy(char *dest, const char *src, size_t dsize);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);
char	*gnl_ft_strjoin(char *s1, char *s2);

#endif