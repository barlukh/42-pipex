/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:40:15 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/25 11:39:00 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static size_t	ft_count_words(char const *s, char c);
static char		**ft_allocate_array(char const *s, char c, char **s_arr);
static void		*ft_free_array(char **s_arr, size_t i);

char	**ft_split(char const *s, char c)
{
	char	**s_arr;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	s_arr = malloc(sizeof(char *) * (word_count + 1));
	if (!s_arr)
		return (NULL);
	s_arr = ft_allocate_array(s, c, s_arr);
	if (!s_arr)
		return (NULL);
	s_arr[word_count] = NULL;
	return (s_arr);
}

// Counts how many words to split the string into.
static size_t	ft_count_words(char const *s, char c)
{
	size_t	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == c || *s == '\n')
			s++;
		if (*s)
		{
			word_count++;
			while (*s && *s != c && *s != '\n')
				s++;
		}
	}
	return (word_count);
}

// Allocates each single word into its array.
static char	**ft_allocate_array(char const *s, char c, char **s_arr)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		while (*s == c || *s == '\n')
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				word_len = ft_strchr(s, c) - s;
			else if (ft_strchr(s, '\n'))
				word_len = ft_strlen(s) - 1;
			else
				word_len = ft_strlen(s);
			s_arr[i] = ft_substr(s, 0, word_len);
			if (!s_arr[i])
				return (ft_free_array(s_arr, i));
			s += word_len;
			i++;
		}
	}
	return (s_arr);
}

// Frees all arrays.
static void	*ft_free_array(char **s_arr, size_t i)
{
	while (i > 0)
		free(s_arr[i--]);
	free(s_arr[i]);
	free(s_arr);
	return (NULL);
}
