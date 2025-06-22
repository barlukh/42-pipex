/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:49:15 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/22 15:51:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_putstr(const char *s, int fd)
{
	size_t	i;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i] != '\0')
	{
		if (write(fd, &s[i], 1) == ERROR)
			return (ERROR);
		i++;
	}
	if (write(1, "\n", 1) == ERROR)
		return (ERROR);
	i++;
	return ((int)i);
}
