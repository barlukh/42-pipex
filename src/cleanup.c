/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:38:18 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/21 11:01:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_pipes(size_t count, t_processes *prcs)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		close(prcs->pipefd[i][0]);
		close(prcs->pipefd[i][1]);
		i++;
	}
}
