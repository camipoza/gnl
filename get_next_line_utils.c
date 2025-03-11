/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoza-ra <cpoza-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:58:40 by cpoza-ra          #+#    #+#             */
/*   Updated: 2025/03/11 19:23:41 by cpoza-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*gnl_ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if ((char)c == '\0')
		return (s);
	return (NULL);
}

size_t	gnl_ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

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
		return (gnl_ft_strdup(""));
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

char	*gnl_ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL)
		s1 = "";
	len1 = gnl_ft_strlen(s1);
	len2 = gnl_ft_strlen(s2);
	s3 = (char *)malloc (len1 + len2 + 1);
	if (!s3)
		return (NULL);
	gnl_ft_strncpy(s3, s1, len1 + len2 + 1);
	gnl_ft_strlcat(s3, s2, len1 + len2 + 1);
	return (s3);
}
