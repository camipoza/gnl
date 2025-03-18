/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:50:00 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/18 16:50:15 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*gnl_extract_line(char *buffer);
char	*ft_readbuffer(int fd, char *rest);
char	*gnl_ft_strchr(char *s, char c);
size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_strdup(const char *s);
char	*gnl_ft_strncpy(char *dest, const char *src, size_t dsize);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);
size_t	gnl_ft_strlcat(char *dest, const char *src, size_t size);
char	*gnl_ft_strjoin(char *s1, char *s2);

#endif