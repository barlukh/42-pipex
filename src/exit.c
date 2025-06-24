/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:47:32 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/24 10:01:58 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	print_system_errno(char *s)
{
	char	*err_s;

	err_s = ft_strjoin("bash: ", s);
	if (!err_s)
		return (EXIT_FAILURE);
	perror(err_s);
	free(err_s);
	return (EXIT_FAILURE);
}

int	print_user_errno(char *s, int err)
{
	char	*err_s;

	errno = err;
	err_s = ft_strjoin("bash: ", s);
	if (!err_s)
		return (EXIT_FAILURE);
	perror(err_s);
	free(err_s);
	return (EXIT_FAILURE);
}
