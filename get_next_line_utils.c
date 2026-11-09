/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboel-ma <aboel-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:53:25 by aboel-ma          #+#    #+#             */
/*   Updated: 2026/11/07 14:53:52 by aboel-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s != NULL && s[index])
		index++;
	return (index);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	src_len;

	index = 0;
	src_len = ft_strlen(src);
	if (size > 0)
	{
		while (src[index] && index < size - 1)
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	j;
	char	*str;

	index = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[index])
	{
		str[index] = s1[index];
		index++;
	}
	while (s2[j])
	{
		str[index] = s2[j];
		index++;
		j++;
	}
	str[index] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	alloc_len;
	char	*str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
	{
		str = malloc(1);
		if (str == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	if (s_len - start <= len)
		alloc_len = s_len - start + 1;
	else
		alloc_len = len + 1;
	str = malloc (sizeof(char) * alloc_len);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s[start], alloc_len);
	return (str);
}

char	*ft_strdup(const char *s)
{
	size_t	index;
	size_t	str_len;
	char	*str;

	index = 0;
	str_len = ft_strlen(s);
	str = malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	while (index < str_len)
	{
		str[index] = s[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}
