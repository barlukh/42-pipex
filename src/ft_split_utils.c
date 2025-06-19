/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:45 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/19 13:55:39 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*ft_strdup(const char *s);
static void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	size_t	substr_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = (size_t)start;
	if (i >= s_len)
		return (ft_strdup(""));
	else if (s_len - i >= len)
		substr_len = len;
	else
		substr_len = s_len - i;
	substr = malloc(sizeof(char) * (substr_len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + i, substr_len);
	substr[substr_len] = '\0';
	return (substr);
}

// Duplicates a string using dynamic memory allocation.
static char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*new_s;
	size_t	i;

	s_len = ft_strlen(s);
	new_s = malloc(sizeof(char) * (s_len + 1));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	ft_memcpy(new_s, s, s_len);
	new_s[s_len] = '\0';
	return (new_s);
}

// Copies bytes from one memory area to another.
static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	const unsigned char	*p_src;
	size_t				i;

	p_dest = (unsigned char *)dest;
	p_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}
