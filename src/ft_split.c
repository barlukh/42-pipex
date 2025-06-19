/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:40:15 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/19 13:44:14 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_word_count(char const *s, char c);
static char	**ft_allocate_array(char const *s, char c, char **arr);
static void	*ft_free_array(char **arr, size_t i);

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**arr;

	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	arr = malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	arr = ft_allocate_array(s, c, arr);
	if (!arr)
		return (NULL);
	arr[word_count] = NULL;
	return (arr);
}

// Counts how many words to split the string into.
static int	ft_word_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c || *s == '\n')
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c && *s != '\n')
				s++;
		}
	}
	return (count);
}

// Allocates each single word into its array.
static char	**ft_allocate_array(char const *s, char c, char **arr)
{
	size_t	word_len;
	size_t	i;

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
			arr[i] = ft_substr(s, 0, word_len);
			if (!arr[i])
				return (ft_free_array(arr, i));
			s += word_len;
			i++;
		}
	}
	return (arr);
}

// Frees all arrays.
static void	*ft_free_array(char **arr, size_t i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr[i]);
	free(arr);
	return (NULL);
}
