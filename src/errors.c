/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:47:32 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/22 14:13:09 by bgazur           ###   ########.fr       */
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

void	close_pipe(t_processes *prcs)
{
	close(prcs->pipefd[0]);
	close(prcs->pipefd[1]);
}
