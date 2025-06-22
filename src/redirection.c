/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:56:36 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/22 15:00:06 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	child_first_fds(char **argv, t_processes *prcs);
static int	child_last_fds(int argc, char **argv, t_processes *prcs);

int	child_fds(int argc, char **argv, size_t i, t_processes *prcs)
{
	if (i == 0)
	{
		if (child_first_fds(argv, prcs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (i == argc - 4)
	{
		if (child_last_fds(argc, argv, prcs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	child_first_fds(char **argv, t_processes *prcs)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close_pipe(prcs);
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1
		|| dup2(prcs->pipefd[1], STDOUT_FILENO) == -1)
	{
		close_pipe(prcs);
		close(fd);
		return (EXIT_FAILURE);
	}
	close_pipe(prcs);
	close(fd);
	return (EXIT_SUCCESS);
}

static int	child_last_fds(int argc, char **argv, t_processes *prcs)
{
	int	fd;

	fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		close_pipe(prcs);
		return (EXIT_FAILURE);
	}
	if (dup2(prcs->pipefd[0], STDIN_FILENO) == -1
		|| dup2(fd, STDOUT_FILENO) == -1)
	{
		close_pipe(prcs);
		close(fd);
		return (EXIT_FAILURE);
	}
	close_pipe(prcs);
	close(fd);
	return (EXIT_SUCCESS);
}
