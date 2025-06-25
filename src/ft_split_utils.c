/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:45 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/25 11:38:01 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*ft_strdup(const char *s);

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
	char	*subs;
	size_t	i;
	size_t	s_len;
	size_t	subs_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = (size_t)start;
	if (i >= s_len)
		return (ft_strdup(""));
	else if (s_len - i >= len)
		subs_len = len;
	else
		subs_len = s_len - i;
	subs = malloc(sizeof(char) * (subs_len + 1));
	if (!subs)
		return (NULL);
	ft_memcpy(subs, s + i, subs_len);
	subs[subs_len] = '\0';
	return (subs);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*p_src;
	unsigned char		*p_dest;
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

// Duplicates a string using dynamic memory allocation.
static char	*ft_strdup(const char *s)
{
	char	*new_s;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	new_s = malloc(sizeof(char) * (s_len + 1));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	ft_memcpy(new_s, s, s_len);
	new_s[s_len] = '\0';
	return (new_s);
}
