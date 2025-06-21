/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:32:46 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/21 11:09:48 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	create_pipes(int argc, t_processes *prcs)
{
	size_t	i;

	prcs->pipefd = malloc(sizeof(int[2]) * (argc - 4));
	if (prcs->pipefd = NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < argc - 4)
	{
		if (pipe(prcs->pipefd[i]) == -1)
		{
			if (i > 0)
				close_pipes(i, prcs);
			free(prcs->pipefd);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_children(int argc, t_processes *prcs)
{
	size_t	i;
	
	prcs->child = malloc(sizeof(pid_t) * (argc - 3));
	if (prcs->child = NULL)
	{
		close_pipes((argc - 4), prcs);
		free(prcs->pipefd);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < argc - 3)
	{
		prcs->child[i] = fork();
		if (prcs->child[i] == (pid_t)-1)
		{
			free(prcs->pipefd);
			free(prcs->child);
			return (EXIT_FAILURE);
		}
		else if (prcs->child[i] == (pid_t)0)
			break ;
		i++;
	}
	return (EXIT_SUCCESS);
}
