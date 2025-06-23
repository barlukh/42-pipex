/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:47:32 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/23 10:09:04 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	print_system_errno(void)
{
	ft_putstr(strerror(errno), STDERR_FILENO);
	return (errno);
}

int	print_user_errno(int err)
{
	errno = err;
	ft_putstr(strerror(errno), STDERR_FILENO);
	return (errno);
}

void	free_split(char **arg)
{
	size_t	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
