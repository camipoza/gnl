/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:58:40 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/18 17:09:47 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*gnl_ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = gnl_ft_strlen(s) + 1;
	dup = (char *)malloc(len);
	if (dup == (NULL))
		return (NULL);
	gnl_ft_strncpy(dup, s, len);
	return (dup);
}

char	*gnl_ft_strncpy(char *dest, const char *src, size_t dsize)
{
	size_t	i;

	i = 0;
	while (i < dsize && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < dsize)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*gnl_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	slen;
	size_t	sublen;

	if (s == NULL)
		return (NULL);
	slen = gnl_ft_strlen(s);
	if (start >= slen)
		return (NULL);
	if (len > slen - start)
		sublen = slen - start;
	else
		sublen = len;
	subs = (char *)malloc(sublen + 1);
	if (subs == NULL)
		return (NULL);
	gnl_ft_strncpy(subs, &s[start], sublen);
	subs[sublen] = '\0';
	return (subs);
}

size_t	gnl_ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	len_dest = 0;
	len_src = 0;
	i = 0;
	while (dest [len_dest] != '\0' && len_dest < size)
		len_dest++;
	while (src [len_src] != '\0')
		len_src++;
	if (size <= len_dest)
		return (size + len_src);
	while (src[i] != '\0' && (len_dest + i) < (size - 1))
	{
		dest [len_dest + i] = src [i];
		i++;
	}
	dest [len_dest + i] = '\0';
	return (len_dest + len_src);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
	{
		s1 = malloc(sizeof(char) + 1);
		if (!s1 || !s2)
			return (NULL);
		s1[0] = '\0';
	}
	str = malloc(sizeof(char) * (gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1));
	if (str)
	{
		while (s1[++i] != '\0')
			str[i] = s1[i];
		while (s2[++j] != '\0')
			str[i + j] = s2[j];
		str[i + j] = '\0';
	}
	free(s1);
	return (str);
}